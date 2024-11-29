#include "fileio.hpp"
#include "metrics.hpp"

// Função para imprimir uma matriz
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    FILEIO reader;

    // Teste com arquivo contendo matriz de adjacências ou Newick
    //std::string filename = "input.txt"; // Modifique para o nome do arquivo adequado
    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " arquivo1.txt arquivo2.txt arquivo3.txt\n";
        return 1;
    }

    std::vector<std::string> filename;
    std::vector<TreeNode*> treenode;

    for (int i = 0; i < 3; i++){
        int index = i + 1;
        filename.push_back(argv[index]);
    }

    Metrics a = Metrics();

    for (int i = 0; i < 3; i++){
        if (reader.readFile(filename[i])) {
            if (reader.hasAdjacencyMatrix()) {
                std::cout << "Matriz de Adjacências Carregada:\n";
                printMatrix(reader.getAdjacencyMatrix());
            } else if (reader.hasNewickTree()) {
                std::cout << "Árvore em formato Newick carregada:\n";
                std::cout << reader.getNewickTree() << "\n";

                treenode.emplace_back(a.parseNewick(reader.getNewickTree())); // Parseando as strings Newick e adicionando ao vetor
            }
        } else {
            std::cerr << "Falha ao processar o arquivo.\n";
        }
    }

    if (reader.hasNewickTree()){
        // Calculando as distâncias
        std::cout << "Distância A -> C: " << a.distance(treenode[0], treenode[2]) << "\n";
        std::cout << "Distância A -> B: " << a.distance(treenode[0], treenode[1]) << "\n";
        std::cout << "Distância B -> C: " << a.distance(treenode[1], treenode[2]) << "\n";

        // Verificando a desigualdade triangular
        if (a.checkTriangularInequality(treenode[0], treenode[1], treenode[2])) {
            std::cout << "\nA desigualdade triangular é satisfeita.\n";
        } else {
            std::cout << "\nA desigualdade triangular não é satisfeita.\n";
        }

        // Limpando a memória
        a.deleteTree(treenode[0]);
        a.deleteTree(treenode[1]);
        a.deleteTree(treenode[2]);
    }

    return 0;
}