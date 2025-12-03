#include "linked_list.h"
#include <stdlib.h>

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};


// constructs a new (empty) list
struct list *list_create(void) {
    struct list *new_list = malloc(sizeof(struct list));
    if (new_list) {
        new_list->first = NULL;
        new_list->last = NULL;
    }
    return new_list;
}


// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list) {
    if (list) {
        struct list_node *current = list->first;
        while (current) {
            struct list_node *next = current->next;
            free(current);
            current = next;
        }
        free(list);
    }
}


// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data) {
    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (!new_node) return;

    new_node->data = item_data;
    new_node->next = NULL;

    if (list->last == NULL) {
        new_node->prev = NULL;
        list->first = new_node;
        list->last = new_node;
    } else {
        new_node->prev = list->last;
        list->last->next = new_node;
        list->last = new_node;
    }
}


// removes item from back of a list
ll_data_t list_pop(struct list *list) {
    if (!list || !list->last) {
        return (ll_data_t)0; // Or some other appropriate default/error value
    }

    struct list_node *last_node = list->last;
    ll_data_t data = last_node->data;

    list->last = last_node->prev;

    if (list->last == NULL) {
        list->first = NULL;
    } else {
        list->last->next = NULL;
    }

    free(last_node);
    return data;
}


// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data) {
    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (!new_node) return;

    new_node->data = item_data;
    new_node->prev = NULL;

    if (list->first == NULL) {
        new_node->next = NULL;
        list->first = new_node;
        list->last = new_node;
    } else {
        new_node->next = list->first;
        list->first->prev = new_node;
        list->first = new_node;
    }
}


// removes item from front of a list
ll_data_t list_shift(struct list *list) {
    if (!list || !list->first) {
        return (ll_data_t)0; // Or some other appropriate default/error value
    }

    struct list_node *first_node = list->first;
    ll_data_t data = first_node->data;

    list->first = first_node->next;

    if (list->first == NULL) {
        list->last = NULL;
    } else {
        list->first->prev = NULL;
    }

    free(first_node);
    return data;
}


// counts the items on a list
size_t list_count(const struct list *list) {
    size_t count = 0;
    const struct list_node *current = list->first;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}


// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data) {
    if (!list) return;

    struct list_node *current = list->first;
    while (current) {
        if (current->data == data) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                list->first = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                list->last = current->prev;
            }

            struct list_node *temp = current;
            current = current->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}