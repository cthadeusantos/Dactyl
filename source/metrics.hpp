#ifndef METRICS_HPP_
#define METRICS_HPP_

#include <iostream>
#include <vector>
#include <cmath> // Para std::abs e std::sqrt
#include <string>
#include <stack>

#include "fileio.hpp"
// // Estrutura de um nó da árvore        
// struct TreeNode {
//     std::vector<TreeNode*> children;
//     std::string label;

//     // Construtor
//     TreeNode(const std::string& lbl = "") : label(lbl) {}
// };

// // Estrutura para a matriz de adjacencias
// using Matrix = std::vector<std::vector<int>>;

class Metrics
{

    public:
        Metrics() {};
        ~Metrics() {};
        
        double distance(const Matrix& tree1, const Matrix& tree2); // for Adjacencies format
        double distance(TreeNode* tree1, TreeNode* tree2); // for Newick format

        bool checkTriangularInequality(const Matrix& A, const Matrix& B, const Matrix& C); // for Adjacencies format
        bool checkTriangularInequality(TreeNode* A, TreeNode* B, TreeNode* C); // for Newick format
        
        TreeNode* parseNewick(const std::string& newick); // for Newick format
        void deleteTree(TreeNode* root); // for Newick format

};
#endif