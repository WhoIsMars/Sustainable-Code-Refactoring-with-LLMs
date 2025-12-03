#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
   size_t count;
};

struct list *list_create(void) {
    struct list *new_list = malloc(sizeof(struct list));
    if (!new_list) return NULL;
    
    new_list->first = NULL;
    new_list->last = NULL;
    new_list->count = 0;
    
    return new_list;
}

void list_destroy(struct list *list) {
    if (!list) return;
    
    struct list_node *current = list->first;
    while (current) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_push(struct list *list, ll_data_t item_data) {
    if (!list) return;
    
    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (!new_node) return;
    
    new_node->data = item_data;
    new_node->next = NULL;
    new_node->prev = list->last;
    
    if (list->last) {
        list->last->next = new_node;
    } else {
        list->first = new_node;
    }
    list->last = new_node;
    list->count++;
}

ll_data_t list_pop(struct list *list) {
    if (!list || !list->last) return (ll_data_t){0};
    
    struct list_node *node = list->last;
    ll_data_t data = node->data;
    
    list->last = node->prev;
    if (list->last) {
        list->last->next = NULL;
    } else {
        list->first = NULL;
    }
    
    free(node);
    list->count--;
    return data;
}

void list_unshift(struct list *list, ll_data_t item_data) {
    if (!list) return;
    
    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (!new_node) return;
    
    new_node->data = item_data;
    new_node->prev = NULL;
    new_node->next = list->first;
    
    if (list->first) {
        list->first->prev = new_node;
    } else {
        list->last = new_node;
    }
    list->first = new_node;
    list->count++;
}

ll_data_t list_shift(struct list *list) {
    if (!list || !list->first) return (ll_data_t){0};
    
    struct list_node *node = list->first;
    ll_data_t data = node->data;
    
    list->first = node->next;
    if (list->first) {
        list->first->prev = NULL;
    } else {
        list->last = NULL;
    }
    
    free(node);
    list->count--;
    return data;
}

size_t list_count(const struct list *list) {
    return list ? list->count : 0;
}

void list_delete(struct list *list, ll_data_t data) {
    if (!list) return;
    
    struct list_node *current = list->first;
    while (current) {
        if (memcmp(&current->data, &data, sizeof(ll_data_t)) == 0) {
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
            list->count--;
            return;
        }
        current = current->next;
    }
}