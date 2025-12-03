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

    return (reversed == original);
}

static void init_factors(factor_t **factors, int a, int b)
{
    assert(factors != NULL);

    *factors = (factor_t *)malloc(sizeof(factor_t));
    assert(*factors != NULL);

    (*factors)->factor_a = a;
    (*factors)->factor_b = b;
    (*factors)->next = NULL;
}

static void insert_factors(factor_t *factors, int a, int b)
{
    while (factors->next != NULL)
    {
        factors = factors->next;
    }

    factors->next = (factor_t *)malloc(sizeof(factor_t));
    assert(factors->next != NULL);

    factors->next->factor_a = a;
    factors->next->factor_b = b;
    factors->next->next = NULL;
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
    product_t *product = (product_t *)calloc(1, sizeof(product_t));
    assert(product != NULL);

    if (from > to)
    {
        snprintf(product->error, MAXERR, "invalid input: min is %d and max is %d", from, to);
        return product;
    }

    for (int i = from; i <= to; i++)
    {
        for (int j = i; j <= to; j++)
        {
            int candidate = i * j;
            if (is_palindrome(candidate))
            {
                if (product->smallest == 0 || candidate < product->smallest)
                {
                    if (product->factors_sm)
                        free_factors(product->factors_sm);
                    init_factors(&product->factors_sm, i, j);
                    product->smallest = candidate;
                }
                else if (candidate == product->smallest)
                {
                    insert_factors(product->factors_sm, i, j);
                }

                if (candidate > product->largest)
                {
                    if (product->factors_lg)
                        free_factors(product->factors_lg);
                    init_factors(&product->factors_lg, i, j);
                    product->largest = candidate;
                }
                else if (candidate == product->largest)
                {
                    insert_factors(product->factors_lg, i, j);
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
    assert(p != NULL);

    if (p->factors_lg)
    {
        free_factors(p->factors_lg);
    }

    if (p->factors_sm)
    {
        free_factors(p->factors_sm);
    }

    free(p);
}