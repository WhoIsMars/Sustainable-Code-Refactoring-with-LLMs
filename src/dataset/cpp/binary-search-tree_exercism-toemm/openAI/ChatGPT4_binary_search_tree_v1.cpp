#include "binary_search_tree.h"

namespace binary_search_tree {

using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    TreeNode* insert(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    TreeNode* remove(TreeNode* node, int value) {
        if (!node) return nullptr;
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
        return node;
    }

    bool search(TreeNode* node, int value) const {
        if (!node) return false;
        if (value == node->value) return true;
        if (value < node->value) return search(node->left, value);
        return search(node->right, value);
    }

    void inorderTraversal(TreeNode* node, vector<int>& result) const {
        if (!node) return;
        inorderTraversal(node->left, result);
        result.push_back(node->value);
        inorderTraversal(node->right, result);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        deleteTree(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    bool search(int value) const {
        return search(root, value);
    }

    vector<int> inorderTraversal() const {
        vector<int> result;
        inorderTraversal(root, result);
        return result;
    }
};

}  // namespace binary_search_tree