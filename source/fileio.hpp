
#ifndef FILEIO_HPP_
#define FILEIO_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

//using Matrix = std::vector<std::vector<int>>;
using Matrix = std::vector<std::vector<int>>;

// Estrutura de nó para a árvore derivada do formato Newick
struct TreeNode {
    std::vector<TreeNode*> children;
    std::string label;

    TreeNode(const std::string& lbl = "") : label(lbl) {}
    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

class FILEIO
{
    private:
        Matrix adjacencyMatrix;
        std::string newickTree;
        bool isMatrixLoaded = false;
        bool isTreeLoaded = false;
        
        void clear();
    
    public:
        bool readFile(const std::string& filename); // Lê o arquivo e determina se é uma matriz de adjacências ou uma árvore em formato Newick
        bool hasAdjacencyMatrix() const ; // Verifica se uma matriz de adjacências foi carregada
        bool hasNewickTree() const; // Verifica se uma matriz de adjacências foi carregada
        const Matrix& getAdjacencyMatrix() const; // Obtém a matriz de adjacências
        const std::string& getNewickTree() const; // Obtém a árvore em formato Newick

};
#endif