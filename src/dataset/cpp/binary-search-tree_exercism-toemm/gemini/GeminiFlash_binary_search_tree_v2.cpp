#include <iostream>
#include <memory>

namespace binary_search_tree {

using namespace std;

template <typename T>
class BinarySearchTree {
 private:
  struct Node {
    T data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;

    Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
  };

  unique_ptr<Node> root;

 public:
  BinarySearchTree() : root(nullptr) {}

  // Insert a value into the BST
  void insert(const T& value) { root = insertRecursive(move(root), value); }

  // Check if a value exists in the BST
  bool contains(const T& value) const { return containsRecursive(root.get(), value); }

  // Delete a value from the BST
  void remove(const T& value) { root = removeRecursive(move(root), value); }

  // Find the minimum value in the BST
  T min() const {
    if (!root) {
      throw runtime_error("Tree is empty");
    }
    Node* current = root.get();
    while (current->left) {
      current = current->left.get();
    }
    return current->data;
  }

  // Find the maximum value in the BST
  T max() const {
    if (!root) {
      throw runtime_error("Tree is empty");
    }
    Node* current = root.get();
    while (current->right) {
      current = current->right.get();
    }
    return current->data;
  }

 private:
  // Recursive helper function for insert
  unique_ptr<Node> insertRecursive(unique_ptr<Node> node, const T& value) {
    if (!node) {
      return make_unique<Node>(value);
    }

    if (value < node->data) {
      node->left = insertRecursive(move(node->left), value);
    } else if (value > node->data) {
      node->right = insertRecursive(move(node->right), value);
    } else {
      // Value already exists, no insertion needed
      return node;
    }

    return node;
  }

  // Recursive helper function for contains
  bool containsRecursive(Node* node, const T& value) const {
    if (!node) {
      return false;
    }

    if (value < node->data) {
      return containsRecursive(node->left.get(), value);
    } else if (value > node->data) {
      return containsRecursive(node->right.get(), value);
    } else {
      return true;
    }
  }

  // Recursive helper function for remove
  unique_ptr<Node> removeRecursive(unique_ptr<Node> node, const T& value) {
    if (!node) {
      return nullptr;
    }

    if (value < node->data) {
      node->left = removeRecursive(move(node->left), value);
    } else if (value > node->data) {
      node->right = removeRecursive(move(node->right), value);
    } else {
      // Node found, perform deletion
      if (!node->left && !node->right) {
        // Case 1: No children
        return nullptr;
      } else if (!node->left) {
        // Case 2: One child (right)
        return move(node->right);
      } else if (!node->right) {
        // Case 3: One child (left)
        return move(node->left);
      } else {
        // Case 4: Two children
        // Find inorder successor (minimum value in the right subtree)
        Node* successor = findMin(node->right.get());
        node->data = successor->data;
        node->right = removeRecursive(move(node->right), successor->data);
      }
    }

    return node;
  }

  // Helper function to find the minimum value in a subtree
  Node* findMin(Node* node) const {
    Node* current = node;
    while (current && current->left) {
      current = current->left.get();
    }
    return current;
  }
};

}  // namespace binary_search_tree