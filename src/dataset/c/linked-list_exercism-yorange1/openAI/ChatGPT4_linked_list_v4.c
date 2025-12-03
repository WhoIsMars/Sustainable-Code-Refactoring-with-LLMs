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
    size_t count;
};

// constructs a new (empty) list
struct list *list_create(void)
{
    struct list *new_list = (struct list *)malloc(sizeof(struct list));
    if (!new_list)
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
    if (!new_node)
    {
        return;
    }

    new_node->data = item_data;
    new_node->prev = list->last;

    if (list->last)
    {
        list->last->next = new_node;
    }
    else
    {
        list->first = new_node;
    }

    list->last = new_node;
    list->count++;
}

// removes item from back of a list
ll_data_t list_pop(struct list *list)
{
    if (!list->last)
    {
        return (ll_data_t){0}; // Return default value if list is empty
    }

    struct list_node *last_node = list->last;
    ll_data_t data = last_node->data;

    list->last = last_node->prev;

    if (list->last)
    {
        list->last->next = NULL;
    }
    else
    {
        list->first = NULL;
    }

    free(last_node);
    list->count--;

    return data;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)calloc(1, sizeof(struct list_node));
    if (!new_node)
    {
        return;
    }

    new_node->data = item_data;
    new_node->next = list->first;

    if (list->first)
    {
        list->first->prev = new_node;
    }
    else
    {
        list->last = new_node;
    }

    list->first = new_node;
    list->count++;
}

// removes item from front of a list
ll_data_t list_shift(struct list *list)
{
    if (!list->first)
    {
        return (ll_data_t){0}; // Return default value if list is empty
    }

    struct list_node *first_node = list->first;
    ll_data_t data = first_node->data;

    list->first = first_node->next;

    if (list->first)
    {
        list->first->prev = NULL;
    }
    else
    {
        list->last = NULL;
    }

    free(first_node);
    list->count--;

    return data;
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *temp = list->first;

    while (temp)
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
            return;
        }

        temp = temp->next;
    }
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list)
{
    struct list_node *current = list->first;

    while (current)
    {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}