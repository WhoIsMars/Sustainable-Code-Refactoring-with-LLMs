#include "palindrome_products.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_palindrome(int number)
{
    if (number < 0) return false;
    if (number < 10) return true;
    
    int original = number;
    int reversed = 0;
    
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    
    return original == reversed;
}

static void init_factors(factor_t **factors, int a, int b)
{
    assert(factors != NULL);

    *factors = (factor_t *)calloc(1, sizeof(factor_t));
    assert(*factors != NULL);

    (*factors)->factor_a = a;
    (*factors)->factor_b = b;
}

static void insert_factors(factor_t *factors, int a, int b)
{
    factor_t *tail = factors;

    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = (factor_t *)calloc(1, sizeof(factor_t));
    assert(tail->next != NULL);

    tail->next->factor_a = a;
    tail->next->factor_b = b;
}

static void free_factors(factor_t *factors)
{
    assert(factors != NULL);

    factor_t *current = factors;
    while (current != NULL) {
        factor_t *next = current->next;
        free(current);
        current = next;
    }
}

product_t *get_palindrome_product(int from, int to)
{
    product_t *product = (product_t *)calloc(1, sizeof(product_t));
    assert(product != NULL);

    if (from > to) {
        snprintf(product->error, MAXERR, "invalid input: min is %d and max is %d", from, to);
        return product;
    }

    int smallest = 0, largest = 0;
    factor_t *factors_sm = NULL, *factors_lg = NULL;

    for (int i = from; i <= to; i++) {
        for (int j = i; j <= to; j++) {
            int candidate = i * j;
            
            if (smallest > 0 && candidate > largest) {
                break;
            }
            
            if (is_palindrome(candidate)) {
                if (smallest == 0) {
                    smallest = largest = candidate;
                    init_factors(&factors_sm, i, j);
                    init_factors(&factors_lg, i, j);
                } else if (candidate < smallest) {
                    if (factors_sm) free_factors(factors_sm);
                    init_factors(&factors_sm, i, j);
                    smallest = candidate;
                } else if (candidate == smallest) {
                    insert_factors(factors_sm, i, j);
                } else if (candidate > largest) {
                    if (factors_lg) free_factors(factors_lg);
                    init_factors(&factors_lg, i, j);
                    largest = candidate;
                } else if (candidate == largest) {
                    insert_factors(factors_lg, i, j);
                }
            }
        }
    }

    if (smallest == 0) {
        snprintf(product->error, MAXERR, "no palindrome with factors in the range %d to %d", from, to);
    } else {
        product->smallest = smallest;
        product->largest = largest;
        product->factors_sm = factors_sm;
        product->factors_lg = factors_lg;
    }

    return product;
}

void free_product(product_t *p)
{
    assert(p != NULL);

    if (p->factors_lg != NULL) {
        free_factors(p->factors_lg);
    }

    if (p->factors_sm != NULL) {
        free_factors(p->factors_sm);
    }

    free(p);
}