#include "react.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

struct reactor *create_reactor()
{
    struct reactor *reactor = (struct reactor *)calloc(1, sizeof(struct reactor));
    assert(reactor != NULL);

    return reactor;
}

void destroy_reactor(struct reactor *reactor)
{
    assert(reactor != NULL);

    struct cell *cell = reactor->cells_head;
    while (cell != NULL)
    {
        struct cell *temp = cell;
        cell = cell->next;
        free(temp);
    }

    free(reactor);
}

static inline void add_cell(struct reactor *reactor, struct cell *cell)
{
    if (reactor->cells_head == NULL)
    {
        reactor->cells_head = cell;
        reactor->cells_tail = cell;
    }
    else
    {
        reactor->cells_tail->next = cell;
        reactor->cells_tail = cell;
    }
}

struct cell *create_input_cell(struct reactor *reactor, int initial_value)
{
    assert(reactor != NULL);

    struct cell *cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(cell != NULL);

    cell->type = INPUT;
    cell->value = initial_value;

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
    assert(false); // Should never reach here if MAX_CELL_OUTPUT is sufficient
}

struct cell *create_compute1_cell(struct reactor *reactor, struct cell *input_cell, compute1 compute)
{
    assert(reactor != NULL && input_cell != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE1;
    compute_cell->inputs[0] = input_cell;
    compute_cell->compute.func1 = compute;

    add_output_cell(input_cell, compute_cell);

    compute_cell->value = compute(input_cell->value);

    add_cell(reactor, compute_cell);

    return compute_cell;
}

struct cell *create_compute2_cell(struct reactor *reactor, struct cell *input_cell1,
                                  struct cell *input_cell2, compute2 compute)
{
    assert(reactor != NULL && input_cell1 != NULL && input_cell2 != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE2;
    compute_cell->inputs[0] = input_cell1;
    compute_cell->inputs[1] = input_cell2;
    compute_cell->compute.func2 = compute;

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
    if (cell->type == COMPUTE1)
    {
        cell->value = cell->compute.func1(cell->inputs[0]->value);
    }
    else if (cell->type == COMPUTE2)
    {
        cell->value = cell->compute.func2(cell->inputs[0]->value, cell->inputs[1]->value);
    }

    return cell->value;
}

static void update_value(struct cell *cell)
{
    if (cell->type != INPUT)
    {
        int prev_value = cell->value;
        compute_value(cell);
        if (cell->value == prev_value)
        {
            return;
        }
    }

    for (size_t i = 0; i < MAX_CELL_OUTPUT && cell->output[i] != NULL; i++)
    {
        update_value(cell->output[i]);
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

    for (size_t i = 0; i < MAX_CELL_OUTPUT && cell->output[i] != NULL; i++)
    {
        check_callbacks(cell->output[i]);
    }
}

void set_cell_value(struct cell *input_cell, int new_value)
{
    assert(input_cell != NULL && input_cell->type == INPUT);

    if (input_cell->value == new_value)
    {
        return;
    }

    input_cell->value = new_value;

    update_value(input_cell);
    check_callbacks(input_cell);
}

callback_id add_callback(struct cell *compute_cell, void *info, callback func)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);

    for (callback_id id = 0; id < MAX_CELL_CALLBACKS_NUM; id++)
    {
        if (compute_cell->callbacks[id].func == NULL)
        {
            compute_cell->callbacks[id].cell_value = compute_cell->value;
            compute_cell->callbacks[id].func = func;
            compute_cell->callbacks[id].info = info;
            return id;
        }
    }
    
    assert(false); // Should never reach here if MAX_CELL_CALLBACKS_NUM is sufficient
    return 0;
}

void remove_callback(struct cell *compute_cell, callback_id id)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);

    compute_cell->callbacks[id].func = NULL;
    compute_cell->callbacks[id].info = NULL;
}