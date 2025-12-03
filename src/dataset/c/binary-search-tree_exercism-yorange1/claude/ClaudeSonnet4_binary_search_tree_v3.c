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
    node_t *current = root;
    
    while (1) {
        if (data <= current->data) {
            if (current->left == NULL) {
                current->left = create_node(data);
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = create_node(data);
                return;
            }
            current = current->right;
        }
    }
}

static size_t count_node(node_t *tree)
{
    if (tree == NULL) return 0;
    
    size_t count = 0;
    node_t *stack[1000];
    int top = -1;
    
    stack[++top] = tree;
    
    while (top >= 0) {
        node_t *current = stack[top--];
        count++;
        
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
    
    return count;
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
    if (tree == NULL) return;
    
    node_t *stack[1000];
    int top = -1;
    
    stack[++top] = tree;
    
    while (top >= 0) {
        node_t *current = stack[top--];
        
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
        
        free(current);
    }
}

static void ldr_traver(node_t *tree, int *sorted_data, size_t *index)
{
    if (tree == NULL) return;
    
    node_t *stack[1000];
    int top = -1;
    node_t *current = tree;
    
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        
        current = stack[top--];
        sorted_data[(*index)++] = current->data;
        current = current->right;
    }
}

int *sorted_data(node_t *tree)
{
    if (tree == NULL) return NULL;
    
    size_t node_num = count_node(tree);

    int *data = (int *)malloc(node_num * sizeof(int));
    assert(data != NULL);

    size_t index = 0;
    ldr_traver(tree, data, &index);

    return data;
}