#include "binary_search_tree.h"
#include <stdlib.h>


void add_node(node_t *tree, int item) {
    node_t *n, *p;

    p = tree;
    n = malloc(sizeof(node_t));
    n->data = item;
    n->left = NULL;
    n->right = NULL;

    while (1) {
        if (item <= p->data && p->left == NULL) {
            p->left = n;
            return;
        }
        if (item <= p->data && p->left != NULL) {
            p = p->left;
            continue;
        }

        if (item > p->data && p->right == NULL) {
            p->right = n;
            return;
        }
        if (item > p->data && p->right != NULL) {
            p = p->right;
            continue;
        }
    }
}

node_t *build_tree(int *tree_data, size_t tree_data_len) {
    if (tree_data_len == 0) {
        return NULL;
    }

    node_t *root;
    root = malloc(sizeof(node_t));
    root->data = tree_data[0];
    root->left = NULL;
    root->right = NULL;
    for (size_t i = 1; i < tree_data_len; i++) {
        add_node(root, tree_data[i]);
    }

    return root;
}

void free_tree(node_t *tree) {
    if (tree->left) {
        free_tree(tree->left);
    }
    if (tree->right) {
        free_tree(tree->right);
    }
    free(tree);
    return;
}

int *sorted_data(node_t *tree) {
    size_t size = tree_size(tree);
    int *res = malloc(size * sizeof(int));
    add_sorted(tree, res, 0);

    return res;
}

size_t tree_size(node_t *tree) {
    size_t tmp = 1;
    if (tree->left) {
        tmp += tree_size(tree->left);
    }
    if (tree->right) {
        tmp += tree_size(tree->right);
    }
    return tmp;
}

size_t add_sorted(node_t *p, int *sorted, size_t index) {
    if (p->left) {
        index = add_sorted(p->left, sorted, index);
    }
    sorted[index++] = p->data;
    if (p->right) {
        index = add_sorted(p->right, sorted, index);
    }
    return index;
}
