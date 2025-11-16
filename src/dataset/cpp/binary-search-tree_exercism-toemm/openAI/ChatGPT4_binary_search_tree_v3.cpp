#include "binary_search_tree.h"

namespace binary_search_tree {

using std::unique_ptr;

struct Node {
    int value;
    unique_ptr<Node> left;
    unique_ptr<Node> right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    unique_ptr<Node> root;

    void insertHelper(unique_ptr<Node>& node, int value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }
        if (value < node->value) {
            insertHelper(node->left, value);
        } else if (value > node->value) {
            insertHelper(node->right, value);
        }
    }

    bool searchHelper(const unique_ptr<Node>& node, int value) const {
        if (!node) return false;
        if (node->value == value) return true;
        return value < node->value ? searchHelper(node->left, value) : searchHelper(node->right, value);
    }

    void inOrderHelper(const unique_ptr<Node>& node, std::vector<int>& result) const {
        if (!node) return;
        inOrderHelper(node->left, result);
        result.push_back(node->value);
        inOrderHelper(node->right, result);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        insertHelper(root, value);
    }

    bool search(int value) const {
        return searchHelper(root, value);
    }

    std::vector<int> inOrderTraversal() const {
        std::vector<int> result;
        inOrderHelper(root, result);
        return result;
    }
};

}  // namespace binary_search_tree