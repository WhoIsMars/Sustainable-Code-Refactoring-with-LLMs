#include "palindrome_products.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_palindrome(int number)
{
    int reversed = 0, original = number;

    while (number > 0)
    {
        reversed = reversed * 10 + (number % 10);
        number /= 10;
    }

    return reversed == original;
}

static factor_t *create_factor(int a, int b)
{
    factor_t *factor = (factor_t *)calloc(1, sizeof(factor_t));
    assert(factor != NULL);

    factor->factor_a = a;
    factor->factor_b = b;
    return factor;
}

static void append_factor(factor_t **head, int a, int b)
{
    factor_t *new_factor = create_factor(a, b);
    if (*head == NULL)
    {
        *head = new_factor;
    }
    else
    {
        factor_t *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_factor;
    }
}

static void free_factors(factor_t *factors)
{
    while (factors != NULL)
    {
        factor_t *temp = factors;
        factors = factors->next;
        free(temp);
    }
}

product_t *get_palindrome_product(int from, int to)
{
    if (from > to)
    {
        product_t *product = (product_t *)calloc(1, sizeof(product_t));
        assert(product != NULL);
        snprintf(product->error, MAXERR, "invalid input: min is %d and max is %d", from, to);
        return product;
    }

    product_t *product = (product_t *)calloc(1, sizeof(product_t));
    assert(product != NULL);

    for (int i = from; i <= to; i++)
    {
        for (int j = i; j <= to; j++)
        {
            int candidate = i * j;
            if (is_palindrome(candidate))
            {
                if (product->smallest == 0 || candidate < product->smallest)
                {
                    free_factors(product->factors_sm);
                    product->factors_sm = NULL;
                    product->smallest = candidate;
                    append_factor(&product->factors_sm, i, j);
                }
                else if (candidate == product->smallest)
                {
                    append_factor(&product->factors_sm, i, j);
                }

                if (candidate > product->largest)
                {
                    free_factors(product->factors_lg);
                    product->factors_lg = NULL;
                    product->largest = candidate;
                    append_factor(&product->factors_lg, i, j);
                }
                else if (candidate == product->largest)
                {
                    append_factor(&product->factors_lg, i, j);
                }
            }
        }
    }

    if (product->smallest == 0)
    {
        snprintf(product->error, MAXERR, "no palindrome with factors in the range %d to %d", from, to);
    }

    return product;
}

void free_product(product_t *p)
{
    if (p == NULL)
        return;

    free_factors(p->factors_lg);
    free_factors(p->factors_sm);
    free(p);
}