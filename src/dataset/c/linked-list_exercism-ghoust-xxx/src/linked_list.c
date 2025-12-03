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
    struct list *new_list;
    new_list = malloc(sizeof(struct list));
    new_list->first = NULL;
    new_list->last = NULL;

    return new_list;
}


// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list) {
    struct list_node *p;
    p = list->first;
    while (p != list->last) {
        list->first = list->first->next;
        free(p);
        p = list->first;
    }
    free(list->last);
    free(list);
}


// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data) {
    struct list_node *new_p;
    new_p = malloc(sizeof(struct list_node));
    new_p->data = item_data;

    new_p->prev = list->last;
    new_p->next = NULL;
    if (list->last) {
        list->last->next = new_p;
    } else {
        list->first = new_p;
    }
    list->last = new_p;
}


// removes item from back of a list
ll_data_t list_pop(struct list *list) {
    struct list_node *tmp;
    ll_data_t tmp_d;

    tmp = list->last;
    tmp_d = list->last->data;
    list->last = list->last->prev;
    if (list->last) {
        list->last->next = NULL;
    } else {
        list->first = NULL;
    }
    free(tmp);

    return tmp_d;
}


// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data) {
    struct list_node *new_p;
    new_p = malloc(sizeof(struct list_node));
    new_p->data = item_data;
    new_p->prev = NULL;

    new_p->next = list->first;
    if (list->first) {
        list->first->prev = new_p;
    } else {
        list->last = new_p;
    }
    list->first = new_p;
}


// removes item from front of a list
ll_data_t list_shift(struct list *list) {
    struct list_node *tmp;
    ll_data_t tmp_d;

    tmp = list->first;
    tmp_d = list->first->data;
    list->first = list->first->next;
    if (list->first) {
        list->first->prev = NULL;
    } else {
        list->last = NULL;
    }
    free(tmp);

    return tmp_d;
}


// counts the items on a list
size_t list_count(const struct list *list) {
    size_t cnt = 0;
    struct list_node *p;
    p = list->first;
    while (p) {
        cnt++;
        p = p->next;
    }

    return cnt;
}


// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data) {
    struct list_node *p;
    p = list->first;
    while (p) {
        if (p->data != data) {
            p = p->next;
            continue;
        }
        if (!p->prev) {
            list_shift(list);
            break;
        }
        if (!p->next) {
            list_pop(list);
            break;
        }

        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);

        break;
    }
}

