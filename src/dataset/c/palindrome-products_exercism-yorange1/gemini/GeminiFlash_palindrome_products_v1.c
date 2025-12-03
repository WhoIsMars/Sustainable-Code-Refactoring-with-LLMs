#include "palindrome_products.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_palindrome(int number) {
    if (number < 0) return false;
    if (number < 10) return true;

    int reversed_number = 0;
    int original_number = number;

    while (number > reversed_number) {
        reversed_number = reversed_number * 10 + number % 10;
        number /= 10;
    }

    return (number == reversed_number) || (number == reversed_number / 10);
}

static void init_factors(factor_t **factors, int a, int b) {
    assert(factors != NULL);

    *factors = (factor_t *)malloc(sizeof(factor_t));
    if (*factors == NULL) {
        perror("Failed to allocate memory for factor_t");
        exit(EXIT_FAILURE);
    }
    (*factors)->factor_a = a;
    (*factors)->factor_b = b;
    (*factors)->next = NULL;
}

static void insert_factors(factor_t *factors, int a, int b) {
    factor_t *new_factor = (factor_t *)malloc(sizeof(factor_t));
    if (new_factor == NULL) {
        perror("Failed to allocate memory for factor_t");
        exit(EXIT_FAILURE);
    }
    new_factor->factor_a = a;
    new_factor->factor_b = b;
    new_factor->next = NULL;

    factor_t *tail = factors;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = new_factor;
}

static void free_factors(factor_t *factors) {
    if (factors == NULL) return;

    factor_t *current = factors;
    while (current != NULL) {
        factor_t *next = current->next;
        free(current);
        current = next;
    }
}

product_t *get_palindrome_product(int from, int to) {
    product_t *product = (product_t *)calloc(1, sizeof(product_t));
    if (product == NULL) {
        perror("Failed to allocate memory for product_t");
        exit(EXIT_FAILURE);
    }

    if (from > to) {
        snprintf(product->error, MAXERR, "invalid input: min is %d and max is %d", from, to);
        return product;
    }

    product->smallest = 0;
    product->largest = 0;
    product->factors_sm = NULL;
    product->factors_lg = NULL;

    for (int i = from; i <= to; i++) {
        for (int j = i; j <= to; j++) {
            int candidate = i * j;
            if (is_palindrome(candidate)) {
                if (product->smallest == 0) {
                    product->smallest = candidate;
                    product->largest = candidate;
                    init_factors(&product->factors_sm, i, j);
                    init_factors(&product->factors_lg, i, j);
                } else if (candidate < product->smallest) {
                    free_factors(product->factors_sm);
                    init_factors(&product->factors_sm, i, j);
                    product->smallest = candidate;
                } else if (candidate == product->smallest) {
                    insert_factors(product->factors_sm, i, j);
                } else if (candidate > product->largest) {
                    free_factors(product->factors_lg);
                    init_factors(&product->factors_lg, i, j);
                    product->largest = candidate;
                } else if (candidate == product->largest) {
                    insert_factors(product->factors_lg, i, j);
                }
            }
        }
    }

    if (product->smallest == 0) {
        snprintf(product->error, MAXERR, "no palindrome with factors in the range %d to %d", from, to);
    }

    return product;
}

void free_product(product_t *p) {
    if (p == NULL) return;

    free_factors(p->factors_lg);
    free_factors(p->factors_sm);
    free(p);
}