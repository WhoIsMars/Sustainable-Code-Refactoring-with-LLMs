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
    size_t size;
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
    new_list->size = 0;

    return new_list;
}

// counts the items on a list
size_t list_count(const struct list *list)
{
    return list->size;
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;
    new_node->next = NULL;

    if (list->size == 0)
    {
        new_node->prev = NULL;
        list->first = new_node;
        list->last = new_node;
    }
    else
    {
        new_node->prev = list->last;
        list->last->next = new_node;
        list->last = new_node;
    }

    list->size++;
}

// removes item from back of a list
ll_data_t list_pop(struct list *list)
{
    if (list->size == 0) return (ll_data_t)0;

    struct list_node *last_node = list->last;
    ll_data_t data = last_node->data;

    if (list->size == 1)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        list->last = last_node->prev;
        list->last->next = NULL;
    }

    free(last_node);
    list->size--;
    return data;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;
    new_node->prev = NULL;

    if (list->size == 0)
    {
        new_node->next = NULL;
        list->first = new_node;
        list->last = new_node;
    }
    else
    {
        new_node->next = list->first;
        list->first->prev = new_node;
        list->first = new_node;
    }

    list->size++;
}

// removes item from front of a list
ll_data_t list_shift(struct list *list)
{
    if (list->size == 0) return (ll_data_t)0;

    struct list_node *first_node = list->first;
    ll_data_t data = first_node->data;

    if (list->size == 1)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        list->first = first_node->next;
        list->first->prev = NULL;
    }

    free(first_node);
    list->size--;
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
            if (temp->prev == NULL)
            {
                list->first = temp->next;
            }
            else
            {
                temp->prev->next = temp->next;
            }

            if (temp->next == NULL)
            {
                list->last = temp->prev;
            }
            else
            {
                temp->next->prev = temp->prev;
            }

            free(temp);
            list->size--;
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
    struct list_node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}