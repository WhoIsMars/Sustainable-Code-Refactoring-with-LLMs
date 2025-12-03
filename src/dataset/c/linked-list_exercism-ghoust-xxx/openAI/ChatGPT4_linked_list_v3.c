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
    return calloc(1, sizeof(struct list));
}

// destroys an entire list
void list_destroy(struct list *list) {
    struct list_node *current = list->first;
    while (current) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data) {
    struct list_node *new_node = malloc(sizeof(struct list_node));
    new_node->data = item_data;
    new_node->prev = list->last;
    new_node->next = NULL;

    if (list->last) {
        list->last->next = new_node;
    } else {
        list->first = new_node;
    }
    list->last = new_node;
}

// removes item from back of a list
ll_data_t list_pop(struct list *list) {
    if (!list->last) return (ll_data_t){0};

    struct list_node *tmp = list->last;
    ll_data_t data = tmp->data;

    list->last = tmp->prev;
    if (list->last) {
        list->last->next = NULL;
    } else {
        list->first = NULL;
    }
    free(tmp);

    return data;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data) {
    struct list_node *new_node = malloc(sizeof(struct list_node));
    new_node->data = item_data;
    new_node->prev = NULL;
    new_node->next = list->first;

    if (list->first) {
        list->first->prev = new_node;
    } else {
        list->last = new_node;
    }
    list->first = new_node;
}

// removes item from front of a list
ll_data_t list_shift(struct list *list) {
    if (!list->first) return (ll_data_t){0};

    struct list_node *tmp = list->first;
    ll_data_t data = tmp->data;

    list->first = tmp->next;
    if (list->first) {
        list->first->prev = NULL;
    } else {
        list->last = NULL;
    }
    free(tmp);

    return data;
}

// counts the items on a list
size_t list_count(const struct list *list) {
    size_t count = 0;
    for (struct list_node *current = list->first; current; current = current->next) {
        count++;
    }
    return count;
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data) {
    for (struct list_node *current = list->first; current; current = current->next) {
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
            free(current);
            return;
        }
    }
}