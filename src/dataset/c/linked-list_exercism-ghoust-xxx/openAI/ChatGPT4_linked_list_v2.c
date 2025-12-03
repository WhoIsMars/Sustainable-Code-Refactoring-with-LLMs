#include "linked_list.h"
#include <stdlib.h>

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
   size_t count; // Added to track the number of elements
};

// constructs a new (empty) list
struct list *list_create(void) {
    struct list *new_list = malloc(sizeof(struct list));
    if (!new_list) return NULL; // Handle allocation failure
    new_list->first = NULL;
    new_list->last = NULL;
    new_list->count = 0; // Initialize count
    return new_list;
}

// destroys an entire list
void list_destroy(struct list *list) {
    if (!list) return; // Handle null pointer
    struct list_node *p = list->first;
    while (p) {
        struct list_node *next = p->next;
        free(p);
        p = next;
    }
    free(list);
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data) {
    if (!list) return; // Handle null pointer
    struct list_node *new_p = malloc(sizeof(struct list_node));
    if (!new_p) return; // Handle allocation failure
    new_p->data = item_data;
    new_p->prev = list->last;
    new_p->next = NULL;
    if (list->last) {
        list->last->next = new_p;
    } else {
        list->first = new_p;
    }
    list->last = new_p;
    list->count++; // Increment count
}

// removes item from back of a list
ll_data_t list_pop(struct list *list) {
    if (!list || !list->last) return (ll_data_t){0}; // Handle empty list
    struct list_node *tmp = list->last;
    ll_data_t tmp_d = tmp->data;
    list->last = tmp->prev;
    if (list->last) {
        list->last->next = NULL;
    } else {
        list->first = NULL;
    }
    free(tmp);
    list->count--; // Decrement count
    return tmp_d;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data) {
    if (!list) return; // Handle null pointer
    struct list_node *new_p = malloc(sizeof(struct list_node));
    if (!new_p) return; // Handle allocation failure
    new_p->data = item_data;
    new_p->prev = NULL;
    new_p->next = list->first;
    if (list->first) {
        list->first->prev = new_p;
    } else {
        list->last = new_p;
    }
    list->first = new_p;
    list->count++; // Increment count
}

// removes item from front of a list
ll_data_t list_shift(struct list *list) {
    if (!list || !list->first) return (ll_data_t){0}; // Handle empty list
    struct list_node *tmp = list->first;
    ll_data_t tmp_d = tmp->data;
    list->first = tmp->next;
    if (list->first) {
        list->first->prev = NULL;
    } else {
        list->last = NULL;
    }
    free(tmp);
    list->count--; // Decrement count
    return tmp_d;
}

// counts the items on a list
size_t list_count(const struct list *list) {
    if (!list) return 0; // Handle null pointer
    return list->count; // Use stored count
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data) {
    if (!list) return; // Handle null pointer
    struct list_node *p = list->first;
    while (p) {
        if (p->data == data) {
            if (p->prev) {
                p->prev->next = p->next;
            } else {
                list->first = p->next;
            }
            if (p->next) {
                p->next->prev = p->prev;
            } else {
                list->last = p->prev;
            }
            free(p);
            list->count--; // Decrement count
            return;
        }
        p = p->next;
    }
}