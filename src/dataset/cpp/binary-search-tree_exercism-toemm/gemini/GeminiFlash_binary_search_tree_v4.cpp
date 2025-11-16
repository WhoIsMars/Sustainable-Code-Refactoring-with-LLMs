#include "binary_search_tree.h"
#include <algorithm>
#include <memory>
#include <stack>
#include <queue>

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
  size_t node_count;

  Node* insert_recursive(Node* node, const T& data) {
    if (!node) {
      return new Node(data);
    }

    if (data < node->data) {
      node->left.reset(insert_recursive(node->left.release(), data));
    } else if (data > node->data) {
      node->right.reset(insert_recursive(node->right.release(), data));
    }
    return node;
  }

  bool contains_recursive(const Node* node, const T& data) const {
    if (!node) {
      return false;
    }

    if (data == node->data) {
      return true;
    } else if (data < node->data) {
      return contains_recursive(node->left.get(), data);
    } else {
      return contains_recursive(node->right.get(), data);
    }
  }

  Node* find_min(Node* node) {
    while (node && node->left) {
      node = node->left.get();
    }
    return node;
  }

  Node* remove_recursive(Node* node, const T& data) {
    if (!node) {
      return nullptr;
    }

    if (data < node->data) {
      node->left.reset(remove_recursive(node->left.release(), data));
    } else if (data > node->data) {
      node->right.reset(remove_recursive(node->right.release(), data));
    } else {
      if (!node->left && !node->right) {
        --node_count;
        return nullptr;
      } else if (!node->left) {
        --node_count;
        return node->right.release();
      } else if (!node->right) {
        --node_count;
        return node->left.release();
      } else {
        Node* min_right = find_min(node->right.get());
        node->data = min_right->data;
        node->right.reset(remove_recursive(node->right.release(), min_right->data));
      }
    }
    return node;
  }

  void in_order_traversal_recursive(const Node* node, vector<T>& result) const {
    if (node) {
      in_order_traversal_recursive(node->left.get(), result);
      result.push_back(node->data);
      in_order_traversal_recursive(node->right.get(), result);
    }
  }

  void pre_order_traversal_recursive(const Node* node, vector<T>& result) const {
    if (node) {
      result.push_back(node->data);
      pre_order_traversal_recursive(node->left.get(), result);
      pre_order_traversal_recursive(node->right.get(), result);
    }
  }

  void post_order_traversal_recursive(const Node* node, vector<T>& result) const {
    if (node) {
      post_order_traversal_recursive(node->left.get(), result);
      post_order_traversal_recursive(node->right.get(), result);
      result.push_back(node->data);
    }
  }

  void clear_recursive(Node* node) {
    if (node) {
      clear_recursive(node->left.release());
      clear_recursive(node->right.release());
    }
  }

public:
  BinarySearchTree() : root(nullptr), node_count(0) {}

  ~BinarySearchTree() {
    clear_recursive(root.release());
  }

  void insert(const T& data) {
    root.reset(insert_recursive(root.release(), data));
    ++node_count;
  }

  bool contains(const T& data) const {
    return contains_recursive(root.get(), data);
  }

  void remove(const T& data) {
    root.reset(remove_recursive(root.release(), data));
  }

  vector<T> in_order_traversal() const {
    vector<T> result;
    in_order_traversal_recursive(root.get(), result);
    return result;
  }

  vector<T> pre_order_traversal() const {
    vector<T> result;
    pre_order_traversal_recursive(root.get(), result);
    return result;
  }

  vector<T> post_order_traversal() const {
    vector<T> result;
    post_order_traversal_recursive(root.get(), result);
    return result;
  }

  size_t size() const {
    return node_count;
  }

  bool empty() const {
    return node_count == 0;
  }

  void clear() {
    clear_recursive(root.release());
    root = nullptr;
    node_count = 0;
  }

  // Level-order traversal (Breadth-First Search)
  vector<T> level_order_traversal() const {
      vector<T> result;
      if (!root) return result;

      queue<Node*> q;
      q.push(root.get());

      while (!q.empty()) {
          Node* current = q.front();
          q.pop();
          result.push_back(current->data);

          if (current->left) q.push(current->left.get());
          if (current->right) q.push(current->right.get());
      }

      return result;
  }
};

}  // namespace binary_search_tree