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

static node_t *add_node(node_t *root, int data)
{
    if (data <= root->data)
    {
        if (root->left == NULL)
        {
            root->left = create_node(data);
            return root->left;
        }
        else
        {
            return add_node(root->left, data);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = create_node(data);
            return root->right;
        }
        else
        {
            return add_node(root->right, data);
        }
    }
}

static size_t count_node(node_t *tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    return 1 + count_node(tree->left) + count_node(tree->right);
}

node_t *build_tree(int *tree_data, size_t tree_data_len)
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

static void ldr_traver(node_t *tree, int *sorted_data, size_t *index)
{
    if (tree == NULL)
    {
        return;
    }

    ldr_traver(tree->left, sorted_data, index);
    sorted_data[(*index)++] = tree->data;
    ldr_traver(tree->right, sorted_data, index);
}

int *sorted_data(node_t *tree)
{
    size_t node_num = count_node(tree);

    int *data = (int *)malloc(node_num * sizeof(int));
    assert(data != NULL);

    size_t index = 0;
    ldr_traver(tree, data, &index);

    return data;
}