#include "binary_search_tree.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <utility> // For std::move

namespace binary_search_tree {

using namespace std;

template <typename T> class binary_search_tree {
private:
  struct node {
    T data;
    unique_ptr<node> left;
    unique_ptr<node> right;

    node(T data) : data(data), left(nullptr), right(nullptr) {}
  };

  unique_ptr<node> root;
  size_t tree_size;

  unique_ptr<node> insert_recursive(unique_ptr<node> n, const T &data) {
    if (!n) {
      return make_unique<node>(data);
    }

    if (data < n->data) {
      n->left = insert_recursive(move(n->left), data);
    } else {
      n->right = insert_recursive(move(n->right), data);
    }
    return n;
  }

  bool contains_recursive(const unique_ptr<node> &n, const T &data) const {
    if (!n) {
      return false;
    }

    if (data == n->data) {
      return true;
    } else if (data < n->data) {
      return contains_recursive(n->left, data);
    } else {
      return contains_recursive(n->right, data);
    }
  }

  unique_ptr<node> remove_recursive(unique_ptr<node> n, const T &data) {
    if (!n) {
      return nullptr;
    }

    if (data < n->data) {
      n->left = remove_recursive(move(n->left), data);
    } else if (data > n->data) {
      n->right = remove_recursive(move(n->right), data);
    } else {
      // Node to be deleted found
      if (!n->left && !n->right) {
        // Case 1: No children
        return nullptr;
      } else if (!n->left) {
        // Case 2: One right child
        return move(n->right);
      } else if (!n->right) {
        // Case 3: One left child
        return move(n->left);
      } else {
        // Case 4: Two children
        // Find inorder successor (smallest in the right subtree)
        node *successor = find_min(n->right.get());
        n->data = successor->data;
        n->right = remove_recursive(move(n->right), successor->data);
      }
    }
    return n;
  }

  node *find_min(node *n) const {
    while (n->left) {
      n = n->left.get();
    }
    return n;
  }

  void in_order_traversal_recursive(const unique_ptr<node> &n,
                                    vector<T> &result) const {
    if (n) {
      in_order_traversal_recursive(n->left, result);
      result.push_back(n->data);
      in_order_traversal_recursive(n->right, result);
    }
  }

public:
  binary_search_tree() : root(nullptr), tree_size(0) {}

  void insert(const T &data) {
    root = insert_recursive(move(root), data);
    tree_size++;
  }

  bool contains(const T &data) const { return contains_recursive(root, data); }

  void remove(const T &data) {
    if (contains(data)) {
      root = remove_recursive(move(root), data);
      tree_size--;
    }
  }

  vector<T> in_order() const {
    vector<T> result;
    in_order_traversal_recursive(root, result);
    return result;
  }

  size_t size() const { return tree_size; }
};

} // namespace binary_search_tree