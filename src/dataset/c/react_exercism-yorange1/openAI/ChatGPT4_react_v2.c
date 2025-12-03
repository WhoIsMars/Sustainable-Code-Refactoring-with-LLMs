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

static void add_cell(struct reactor *reactor, struct cell *cell)
{
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

    struct cell *cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(cell != NULL);

    cell->type = INPUT;
    cell->value = initial_value;

    add_cell(reactor, cell);

    return cell;
}

static void add_output_cell(struct cell *cell, struct cell *output)
{
    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        if (cell->output[i] == NULL)
        {
            cell->output[i] = output;
            return;
        }
    }
    assert(false); // No available slot for output
}

struct cell *create_compute1_cell(struct reactor *reactor, struct cell *input_cell, compute1 compute)
{
    assert(reactor != NULL && input_cell != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE1;
    compute_cell->inputs[0] = input_cell;
    compute_cell->compute.func1 = compute;
    compute_cell->value = compute(input_cell->value);

    add_output_cell(input_cell, compute_cell);
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
    compute_cell->value = compute(input_cell1->value, input_cell2->value);

    add_output_cell(input_cell1, compute_cell);
    add_output_cell(input_cell2, compute_cell);
    add_cell(reactor, compute_cell);

    return compute_cell;
}

int get_cell_value(struct cell *cell)
{
    assert(cell != NULL);
    return cell->value;
}

static int compute_value(struct cell *cell)
{
    if (cell->type == COMPUTE1)
    {
        return cell->compute.func1(cell->inputs[0]->value);
    }
    else if (cell->type == COMPUTE2)
    {
        return cell->compute.func2(cell->inputs[0]->value, cell->inputs[1]->value);
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
        if (cell->output[i] != NULL)
        {
            update_value(cell->output[i]);
        }
    }
}

static void check_callbacks(struct cell *cell)
{
    for (size_t i = 0; i < MAX_CELL_CALLBACKS_NUM; i++)
    {
        struct compute_callback *callback = &cell->callbacks[i];
        if (callback->func != NULL && callback->cell_value != cell->value)
        {
            callback->func(callback->info, cell->value);
            callback->cell_value = cell->value;
        }
    }

    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        if (cell->output[i] != NULL)
        {
            check_callbacks(cell->output[i]);
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
    assert(false); // No available slot for callback
    return -1; // Unreachable
}

void remove_callback(struct cell *compute_cell, callback_id id)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);
    assert(id < MAX_CELL_CALLBACKS_NUM);

    compute_cell->callbacks[id].func = NULL;
    compute_cell->callbacks[id].info = NULL;
}