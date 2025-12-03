#include "binary_search_tree.h"
#include <stdlib.h>

void add_node(node_t *tree, int item) {
    node_t *n = malloc(sizeof(node_t));
    if (!n) return; // Handle allocation failure

    n->data = item;
    n->left = NULL;
    n->right = NULL;

    node_t *p = tree;
    while (1) {
        if (item <= p->data) {
            if (p->left == NULL) {
                p->left = n;
                return;
            } else {
                p = p->left;
            }
        } else {
            if (p->right == NULL) {
                p->right = n;
                return;
            } else {
                p = p->right;
            }
        }
    }
}


node_t *build_tree(int *tree_data, size_t tree_data_len) {
    if (tree_data_len == 0) {
        return NULL;
    }

    node_t *root = malloc(sizeof(node_t));
    if (!root) return NULL; // Handle allocation failure

    root->data = tree_data[0];
    root->left = NULL;
    root->right = NULL;

    for (size_t i = 1; i < tree_data_len; i++) {
        add_node(root, tree_data[i]);
    }

    return root;
}

void free_tree(node_t *tree) {
    if (tree == NULL) return; // Handle null tree

    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}


size_t tree_size(node_t *tree) {
    if (tree == NULL) return 0;

    return 1 + tree_size(tree->left) + tree_size(tree->right);
}

void add_sorted_recursive(node_t *p, int *sorted, size_t *index) {
    if (p == NULL) return;

    add_sorted_recursive(p->left, sorted, index);
    sorted[(*index)++] = p->data;
    add_sorted_recursive(p->right, sorted, index);
}

int *sorted_data(node_t *tree) {
    if (tree == NULL) return NULL;

    size_t size = tree_size(tree);
    int *res = malloc(size * sizeof(int));
    if (!res) return NULL; // Handle allocation failure

    size_t index = 0;
    add_sorted_recursive(tree, res, &index);

    return res;
}