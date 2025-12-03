#include "binary_search_tree.h"
#include <stdlib.h>

void add_node(node_t *tree, int item) {
    node_t *p = tree;
    
    while (1) {
        if (item <= p->data) {
            if (p->left == NULL) {
                p->left = malloc(sizeof(node_t));
                p->left->data = item;
                p->left->left = NULL;
                p->left->right = NULL;
                return;
            }
            p = p->left;
        } else {
            if (p->right == NULL) {
                p->right = malloc(sizeof(node_t));
                p->right->data = item;
                p->right->left = NULL;
                p->right->right = NULL;
                return;
            }
            p = p->right;
        }
    }
}

node_t *build_tree(int *tree_data, size_t tree_data_len) {
    if (tree_data_len == 0) {
        return NULL;
    }

    node_t *root = malloc(sizeof(node_t));
    root->data = tree_data[0];
    root->left = NULL;
    root->right = NULL;
    
    for (size_t i = 1; i < tree_data_len; i++) {
        add_node(root, tree_data[i]);
    }

    return root;
}

void free_tree(node_t *tree) {
    if (tree == NULL) return;
    
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

int *sorted_data(node_t *tree) {
    size_t size = tree_size(tree);
    int *res = malloc(size * sizeof(int));
    add_sorted(tree, res, 0);
    return res;
}

size_t tree_size(node_t *tree) {
    if (tree == NULL) return 0;
    
    return 1 + tree_size(tree->left) + tree_size(tree->right);
}

size_t add_sorted(node_t *p, int *sorted, size_t index) {
    if (p == NULL) return index;
    
    index = add_sorted(p->left, sorted, index);
    sorted[index++] = p->data;
    return add_sorted(p->right, sorted, index);
}