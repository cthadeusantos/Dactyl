
#include "metrics.hpp"

// Função para calcular a distância entre duas árvores representadas por matrizes de adjacência
double Metrics::distance(const Matrix& tree1, const Matrix& tree2) {
    int n = tree1.size();
    double sum = 0.0;

    // Calcula a diferença entre as matrizes
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum += std::pow(tree1[i][j] - tree2[i][j], 2);
        }
    }

    // Retorna a distância de Frobenius (ou similar)
    return std::sqrt(sum);
}

// Função para verificar a desigualdade triangular entre três árvores
bool Metrics::checkTriangularInequality(const Matrix& A, const Matrix& B, const Matrix& C) {
    double dAC = distance(A, C);
    double dAB = distance(A, B);
    double dBC = distance(B, C);

    // Verifica se d(A, C) <= d(A, B) + d(B, C)
    return dAC <= (dAB + dBC);
}


// For Newick format


// Função para criar uma árvore a partir de uma string Newick
TreeNode* Metrics::parseNewick(const std::string& newick) {
    std::stack<TreeNode*> nodeStack;
    TreeNode* current = nullptr;
    std::string label = "";

    for (char ch : newick) {
        if (ch == '(') {
            TreeNode* newNode = new TreeNode();
            if (current) {
                current->children.push_back(newNode);
            }
            nodeStack.push(current);
            current = newNode;
        } else if (ch == ',') {
            if (!label.empty()) {
                current->label = label;
                label = "";
            }
        } else if (ch == ')') {
            if (!label.empty()) {
                current->label = label;
                label = "";
            }
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            }
        } else if (ch == ';') {
            if (!label.empty()) {
                current->label = label;
            }
        } else {
            label += ch; // Acumula o rótulo
        }
    }

    return current; // Raiz da árvore
}

// Função para calcular a distância entre duas árvores
// Aqui, usamos uma distância de exemplo baseada na contagem do número de nós diferentes.
double Metrics::distance(TreeNode* tree1, TreeNode* tree2) {
    if (!tree1 && !tree2) return 0.0;
    if (!tree1 || !tree2) return 1.0;

    // Comparação simples de rótulos
    double labelDiff = (tree1->label != tree2->label) ? 1.0 : 0.0;

    size_t maxChildren = std::max(tree1->children.size(), tree2->children.size());
    double childDiff = 0.0;

    for (size_t i = 0; i < maxChildren; ++i) {
        TreeNode* child1 = (i < tree1->children.size()) ? tree1->children[i] : nullptr;
        TreeNode* child2 = (i < tree2->children.size()) ? tree2->children[i] : nullptr;
        childDiff += distance(child1, child2);
    }

    return labelDiff + childDiff;
}

// Função para verificar a desigualdade triangular
bool Metrics::checkTriangularInequality(TreeNode* A, TreeNode* B, TreeNode* C) {
    double dAC = distance(A, C);
    double dAB = distance(A, B);
    double dBC = distance(B, C);

    return dAC <= (dAB + dBC);
}

// Função para deletar a árvore e liberar memória
void Metrics::deleteTree(TreeNode* root) {
    if (!root) return;
    for (auto child : root->children) {
        deleteTree(child);
    }
    delete root;
}