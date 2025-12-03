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

size_t list_count(const struct list *list)
{
    return list->count;
}

void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;
    new_node->next = NULL;

    if (list->count == 0)
    {
        list->first = new_node;
        new_node->prev = NULL;
    }
    else
    {
        new_node->prev = list->last;
        list->last->next = new_node;
    }

    list->last = new_node;
    list->count++;
}

ll_data_t list_pop(struct list *list)
{
    struct list_node *node_to_remove = list->last;
    ll_data_t data = node_to_remove->data;

    list->last = node_to_remove->prev;

    if (NULL == list->last)
    {
        list->first = NULL;
    }
    else
    {
        list->last->next = NULL;
    }

    free(node_to_remove);
    list->count--;

    return data;
}

void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;
    new_node->prev = NULL;

    if (list->count == 0)
    {
        list->first = new_node;
        list->last = new_node;
        new_node->next = NULL;
    }
    else
    {
        new_node->next = list->first;
        list->first->prev = new_node;
        list->first = new_node;
    }

    list->count++;
}

ll_data_t list_shift(struct list *list)
{
    struct list_node *node_to_remove = list->first;
    ll_data_t data = node_to_remove->data;

    list->first = node_to_remove->next;

    if (NULL == list->first)
    {
        list->last = NULL;
    }
    else
    {
        list->first->prev = NULL;
    }

    free(node_to_remove);
    list->count--;

    return data;
}

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