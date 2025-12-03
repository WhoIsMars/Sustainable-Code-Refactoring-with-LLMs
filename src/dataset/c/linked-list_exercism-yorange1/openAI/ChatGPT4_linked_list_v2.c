#include "linked_list.h"

#include <stdlib.h>

struct list_node
{
    struct list_node *prev, *next;
    ll_data_t data;
};

struct list
{
    struct list_node *first, *last;
    size_t count; // Added to track the count of nodes
};

// constructs a new (empty) list
struct list *list_create(void)
{
    struct list *new_list = (struct list *)malloc(sizeof(struct list));
    if (NULL == new_list)
    {
        return NULL;
    }

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->count = 0;

    return new_list;
}

// counts the items on a list
size_t list_count(const struct list *list)
{
    return list->count;
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)calloc(1, sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;

    if (list->count == 0)
    {
        list->first = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    else
    {
        new_node->prev = list->last;
        list->last->next = new_node;
        new_node->next = NULL;
    }

    list->last = new_node;
    list->count++;
}

// removes item from back of a list
ll_data_t list_pop(struct list *list)
{
    if (list->count == 0)
    {
        return (ll_data_t){0}; // Return default value if list is empty
    }

    struct list_node *prev_node = list->last->prev;
    ll_data_t data = list->last->data;

    free(list->last);

    if (NULL == prev_node)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        prev_node->next = NULL;
        list->last = prev_node;
    }

    list->count--;
    return data;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)calloc(1, sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;

    if (list->count == 0)
    {
        list->first = new_node;
        list->last = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    else
    {
        struct list_node *front_node = list->first;
        front_node->prev = new_node;

        new_node->next = front_node;
        new_node->prev = NULL;

        list->first = new_node;
    }

    list->count++;
}

// removes item from front of a list
ll_data_t list_shift(struct list *list)
{
    if (list->count == 0)
    {
        return (ll_data_t){0}; // Return default value if list is empty
    }

    struct list_node *next_node = list->first->next;
    ll_data_t data = list->first->data;

    free(list->first);

    if (NULL == next_node)
    {
        list->last = NULL;
        list->first = NULL;
    }
    else
    {
        next_node->prev = NULL;
        list->first = next_node;
    }

    list->count--;
    return data;
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *temp = list->first;

    while (temp != NULL)
    {
        if (temp->data == data)
        {
            if (temp == list->first)
            {
                list_shift(list);
            }
            else if (temp == list->last)
            {
                list_pop(list);
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free(temp);
                list->count--;
            }

            break;
        }

        temp = temp->next;
    }
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list)
{
    struct list_node *current = list->first;
    while (current != NULL)
    {
        struct list_node *temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}