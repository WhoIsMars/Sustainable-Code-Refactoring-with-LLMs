#include "binary_search_tree.h"

#include <assert.h>
#include <stdlib.h>

static node_t *create_node(int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    assert(node != NULL);

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void add_node(node_t *root, int data)
{
    while (1)
    {
        node_t **node = data <= root->data ? &root->left : &root->right;

        if (*node == NULL)
        {
            *node = create_node(data);
            return;
        }
        root = *node;
    }
}

static size_t count_node(const node_t *tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    size_t left_count = count_node(tree->left);
    size_t right_count = count_node(tree->right);

    return 1 + left_count + right_count;
}

node_t *build_tree(const int *tree_data, size_t tree_data_len)
{
    assert(tree_data != NULL && tree_data_len > 0);

    node_t *root = create_node(tree_data[0]);

    for (size_t i = 1; i < tree_data_len; i++)
    {
        add_node(root, tree_data[i]);
    }

    return root;
}

void free_tree(node_t *tree)
{
    if (tree == NULL)
    {
        return;
    }

    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

static void ldr_traver(const node_t *tree, int *sorted_data, size_t *index)
{
    if (tree == NULL)
    {
        return;
    }

    ldr_traver(tree->left, sorted_data, index);
    sorted_data[(*index)++] = tree->data;
    ldr_traver(tree->right, sorted_data, index);
}

int *sorted_data(const node_t *tree)
{
    size_t node_num = count_node(tree);
    if (node_num == 0)
    {
        return NULL;
    }

    int *data = (int *)malloc(node_num * sizeof(int));
    assert(data != NULL);

    size_t index = 0;
    ldr_traver(tree, data, &index);

    return data;
}