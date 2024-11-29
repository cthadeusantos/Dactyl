#include "fileio.hpp"

// Limpa as variáveis internas
void FILEIO::clear() {
    adjacencyMatrix.clear();
    newickTree.clear();
    isMatrixLoaded = false;
    isTreeLoaded = false;
}

// Lê o arquivo e determina se é uma matriz de adjacências ou uma árvore em formato Newick
bool FILEIO::readFile(const std::string& filename) {
    clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << "\n";
        return false;
    }

    std::string line;
    if (std::getline(file, line)) {
        if (line.find('(') != std::string::npos && line.find(';') != std::string::npos) {
            // Formato Newick
            newickTree = line;
            isTreeLoaded = true;
        } else {
            // Matriz de adjacências
            std::stringstream ss(line);
            std::vector<int> row;
            int value;
            while (ss >> value) {
                row.push_back(value);
            }
            adjacencyMatrix.push_back(row);

            // Lê as demais linhas
            while (std::getline(file, line)) {
                row.clear();
                ss.clear();
                ss.str(line);
                while (ss >> value) {
                    row.push_back(value);
                }
                adjacencyMatrix.push_back(row);
            }
            isMatrixLoaded = true;
        }
    }
    file.close();
    return true;
}

// Verifica se uma matriz de adjacências foi carregada
bool FILEIO::hasAdjacencyMatrix() const {
    return isMatrixLoaded;
}

// Verifica se uma árvore em Newick foi carregada
bool FILEIO::hasNewickTree() const {
    return isTreeLoaded;
}

// Obtém a matriz de adjacências
const Matrix& FILEIO::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

// Obtém a árvore em formato Newick
const std::string& FILEIO::getNewickTree() const {
    return newickTree;
}