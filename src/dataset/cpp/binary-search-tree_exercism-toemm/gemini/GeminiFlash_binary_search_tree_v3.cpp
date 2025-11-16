#include "binary_search_tree.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <utility>

namespace binary_search_tree {

using namespace std;

template <typename T> class BinarySearchTree {
private:
  struct Node {
    T data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;

    Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
  };

  unique_ptr<Node> root;
  size_t node_count;

  Node *insert_recursive(Node *node, const T &value) {
    if (!node) {
      return new Node(value);
    }

    if (value < node->data) {
      node->left.reset(insert_recursive(node->left.release(), value));
    } else if (value > node->data) {
      node->right.reset(insert_recursive(node->right.release(), value));
    }

    return node;
  }

  Node *find_recursive(Node *node, const T &value) const {
    if (!node) {
      return nullptr;
    }

    if (value == node->data) {
      return node;
    } else if (value < node->data) {
      return find_recursive(node->left.get(), value);
    } else {
      return find_recursive(node->right.get(), value);
    }
  }

  Node *find_min_recursive(Node *node) const {
    if (!node) {
      return nullptr;
    }

    if (!node->left) {
      return node;
    }

    return find_min_recursive(node->left.get());
  }

  Node *remove_recursive(Node *node, const T &value) {
    if (!node) {
      return nullptr;
    }

    if (value < node->data) {
      node->left.reset(remove_recursive(node->left.release(), value));
    } else if (value > node->data) {
      node->right.reset(remove_recursive(node->right.release(), value));
    } else {
      if (!node->left && !node->right) {
        return nullptr;
      } else if (!node->left) {
        return node->right.release();
      } else if (!node->right) {
        return node->left.release();
      } else {
        Node *min_right = find_min_recursive(node->right.get());
        node->data = min_right->data;
        node->right.reset(remove_recursive(node->right.release(), min_right->data));
      }
    }
    return node;
  }

  void inorder_traversal_recursive(Node *node,
                                  std::vector<T> &result) const {
    if (node) {
      inorder_traversal_recursive(node->left.get(), result);
      result.push_back(node->data);
      inorder_traversal_recursive(node->right.get(), result);
    }
  }

  void clear_recursive(Node *node) {
    if (node) {
      clear_recursive(node->left.release());
      clear_recursive(node->right.release());
    }
  }

public:
  BinarySearchTree() : root(nullptr), node_count(0) {}

  ~BinarySearchTree() { clear(); }

  void insert(const T &value) {
    root.reset(insert_recursive(root.release(), value));
    node_count++;
  }

  bool find(const T &value) const { return find_recursive(root.get(), value); }

  void remove(const T &value) {
    if (find(value)) {
      root.reset(remove_recursive(root.release(), value));
      node_count--;
    }
  }

  std::vector<T> inorder_traversal() const {
    std::vector<T> result;
    inorder_traversal_recursive(root.get(), result);
    return result;
  }

  size_t size() const { return node_count; }

  bool empty() const { return node_count == 0; }

  void clear() {
    clear_recursive(root.release());
    node_count = 0;
  }
};

} // namespace binary_search_tree