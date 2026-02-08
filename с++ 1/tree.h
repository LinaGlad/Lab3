#ifndef TREE_H
#define TREE_H

#include <string>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Tree {
private:
    struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;

public:
    Tree() {
        root = nullptr;
    }

    ~Tree() {
        clearTreeRecursive(root);
    }

    TreeNode* createNode(int key) {
        TreeNode* newNode = new TreeNode;
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    bool insertRecursive(TreeNode*& node, int key) {
        if (node == nullptr) {
            node = createNode(key);
            return true;
        }

        if (key < node->key) {
            return insertRecursive(node->left, key);
        }
        else if (key > node->key) {
            return insertRecursive(node->right, key);
        }
        else {
            return false;
        }
    }

    bool insert(int key) {
        return insertRecursive(root, key);
    }

    bool searchRecursive(TreeNode* node, int key) {
        if (node == nullptr) return false;

        if (node->key == key) return true;

        if (key < node->key) {
            return searchRecursive(node->left, key);
        }
        else {
            return searchRecursive(node->right, key);
        }
    }

    bool isFullRecursive(TreeNode* node) {
        if (node == nullptr) return true;

        if (node->left == nullptr && node->right == nullptr) return true;

        if (node->left != nullptr && node->right != nullptr) {
            return isFullRecursive(node->left) && isFullRecursive(node->right);
        }
        return false;
    }

    void printInOrderRecursive(TreeNode* node) {
        if (node != nullptr) {
            printInOrderRecursive(node->left);
            std::cout << node->key << " ";
            printInOrderRecursive(node->right);
        }
    }

    void printInOrderIterative(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        std::vector<TreeNode*> nodeStack;
        TreeNode* current = node;

        while (current != nullptr || !nodeStack.empty()) {
            while (current != nullptr) {
                nodeStack.push_back(current);
                current = current->left;
            }

            current = nodeStack.back();
            nodeStack.pop_back();

            std::cout << current->key << " ";

            current = current->right;
        }
        std::cout << std::endl;
    }

    void printPreOrderRecursive(TreeNode* node) {
        if (node != nullptr) {
            std::cout << node->key << " ";
            printPreOrderRecursive(node->left);
            printPreOrderRecursive(node->right);
        }
    }

    void printPostOrderRecursive(TreeNode* node) {
        if (node != nullptr) {
            printPostOrderRecursive(node->left);
            printPostOrderRecursive(node->right);
            std::cout << node->key << " ";
        }
    }

    void printLevelSimple(TreeNode* node, int level, bool& printed) {
        if (node == nullptr) return;

        if (level == 1) {
            std::cout << node->key << " ";
            printed = true;
        }
        else {
            printLevelSimple(node->left, level - 1, printed);
            printLevelSimple(node->right, level - 1, printed);
        }
    }

    void printLevelOrderRecursive(TreeNode* node) {
        if (node == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        
        int level = 1;
        bool printedThisLevel;

        do {
            printedThisLevel = false;
            printLevelSimple(node, level, printedThisLevel);
            level++;
        } while (printedThisLevel);
        std::cout << std::endl;  
    }

    void clearTreeRecursive(TreeNode*& node) {
        if (node == nullptr) return;
        clearTreeRecursive(node->left);
        clearTreeRecursive(node->right);
        delete node;
        node = nullptr;
    }

    void serializeRecursive(TreeNode* node, std::vector<int>& elements) const {
        if (node == nullptr) return;
        elements.push_back(node->key);
        serializeRecursive(node->left, elements);
        serializeRecursive(node->right, elements);
    }
    
    TreeNode* getRoot() const { return root; }
    
    void setRoot(TreeNode* newRoot) {
        clearTreeRecursive(root);
        root = newRoot;
    }
};

#endif
