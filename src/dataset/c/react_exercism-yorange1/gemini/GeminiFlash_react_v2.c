#include "react.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

struct reactor *create_reactor()
{
    struct reactor *reactor = (struct reactor *)malloc(sizeof(struct reactor));
    assert(reactor != NULL);
    reactor->cells_head = NULL;
    reactor->cells_tail = NULL;

    return reactor;
}

void destroy_reactor(struct reactor *reactor)
{
    assert(reactor != NULL);

    struct cell *cell = reactor->cells_head;
    while (cell != NULL)
    {
        struct cell *next = cell->next;
        free(cell);
        cell = next;
    }

    free(reactor);
}

static inline void add_cell(struct reactor *reactor, struct cell *cell)
{
    cell->next = NULL;
    if (reactor->cells_tail)
    {
        reactor->cells_tail->next = cell;
    }
    else
    {
        reactor->cells_head = cell;
    }
    reactor->cells_tail = cell;
}

struct cell *create_input_cell(struct reactor *reactor, int initial_value)
{
    assert(reactor != NULL);

    struct cell *cell = (struct cell *)malloc(sizeof(struct cell));
    assert(cell != NULL);

    cell->type = INPUT;
    cell->value = initial_value;

    for (size_t i = 0; i < MAX_CELL_OUTPUT; ++i) {
        cell->output[i] = NULL;
    }

    add_cell(reactor, cell);

    return cell;
}

static inline void add_output_cell(struct cell *cell, struct cell *output)
{
    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        if (cell->output[i] == NULL)
        {
            cell->output[i] = output;
            return;
        }
    }
    assert(false); // MAX_CELL_OUTPUT exceeded
}

struct cell *create_compute1_cell(struct reactor *reactor, struct cell *input_cell, compute1 compute)
{
    assert(reactor != NULL && input_cell != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)malloc(sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE1;
    compute_cell->inputs[0] = input_cell;
    compute_cell->compute.func1 = compute;

    for (size_t i = 0; i < MAX_CELL_OUTPUT; ++i) {
        compute_cell->output[i] = NULL;
    }

    for (size_t i = 0; i < MAX_CELL_CALLBACKS_NUM; ++i) {
        compute_cell->callbacks[i].func = NULL;
    }

    add_output_cell(input_cell, compute_cell);

    compute_cell->value = compute(input_cell->value);

    add_cell(reactor, compute_cell);

    return compute_cell;
}

struct cell *create_compute2_cell(struct reactor *reactor, struct cell *input_cell1,
                                  struct cell *input_cell2, compute2 compute)
{
    assert(reactor != NULL && input_cell1 != NULL && input_cell2 != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)malloc(sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE2;
    compute_cell->inputs[0] = input_cell1;
    compute_cell->inputs[1] = input_cell2;
    compute_cell->compute.func2 = compute;

    for (size_t i = 0; i < MAX_CELL_OUTPUT; ++i) {
        compute_cell->output[i] = NULL;
    }

    for (size_t i = 0; i < MAX_CELL_CALLBACKS_NUM; ++i) {
        compute_cell->callbacks[i].func = NULL;
    }

    add_output_cell(input_cell1, compute_cell);
    add_output_cell(input_cell2, compute_cell);

    compute_cell->value = compute(input_cell1->value, input_cell2->value);

    add_cell(reactor, compute_cell);

    return compute_cell;
}

int get_cell_value(struct cell *cell)
{
    assert(cell != NULL);

    return cell->value;
}

static inline int compute_value(struct cell *cell)
{
    if (COMPUTE1 == cell->type)
    {
        cell->value = cell->compute.func1(cell->inputs[0]->value);
    }
    else
    {
        cell->value = cell->compute.func2(cell->inputs[0]->value, cell->inputs[1]->value);
    }

    return cell->value;
}

static void update_value(struct cell *cell)
{
    if (cell->type != INPUT)
    {
        int new_value = compute_value(cell);
        if (new_value == cell->value)
        {
            return;
        }
        cell->value = new_value;
    }

    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        struct cell *output = cell->output[i];
        if (output != NULL)
        {
            update_value(output);
        }
    }
}

static void check_callbacks(struct cell *cell)
{
    if (cell->type != INPUT)
    {
        for (size_t i = 0; i < MAX_CELL_CALLBACKS_NUM; i++)
        {
            compute_callback_t *callback = &cell->callbacks[i];

            if (callback->func != NULL)
            {
                if (cell->value != callback->cell_value)
                {
                    callback->func(callback->info, cell->value);
                    callback->cell_value = cell->value;
                }
            }
        }
    }

    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        struct cell *output = cell->output[i];
        if (output != NULL)
        {
            check_callbacks(output);
        }
    }
}

void set_cell_value(struct cell *input_cell, int new_value)
{
    assert(input_cell != NULL && input_cell->type == INPUT);

    if (input_cell->value != new_value)
    {
        input_cell->value = new_value;
        update_value(input_cell);
        check_callbacks(input_cell);
    }
}

callback_id add_callback(struct cell *compute_cell, void *info, callback func)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);

    struct compute_callback *callbacks = compute_cell->callbacks;

    for (callback_id id = 0; id < MAX_CELL_CALLBACKS_NUM; id++)
    {
        if (callbacks[id].func == NULL)
        {
            callbacks[id].cell_value = compute_cell->value;
            callbacks[id].func = func;
            callbacks[id].info = info;
            return id;
        }
    }
    assert(false); // MAX_CELL_CALLBACKS_NUM exceeded

    return MAX_CELL_CALLBACKS_NUM; // Indicate failure, though assert should prevent this.
}

void remove_callback(struct cell *compute_cell, callback_id id)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);
    assert(id < MAX_CELL_CALLBACKS_NUM);

    struct compute_callback *callbacks = compute_cell->callbacks;

    callbacks[id].func = NULL;
    callbacks[id].info = NULL;
}