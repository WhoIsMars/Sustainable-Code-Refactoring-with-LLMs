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

    char str[20];
    snprintf(str, sizeof(str), "%d", number);
    size_t len = strlen(str);

    for (size_t i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

static factor_t *create_factor(int a, int b) {
    factor_t *new_factor = (factor_t *)malloc(sizeof(factor_t));
    if (new_factor == NULL) {
        perror("Failed to allocate memory for factor");
        exit(EXIT_FAILURE);
    }
    new_factor->factor_a = a;
    new_factor->factor_b = b;
    new_factor->next = NULL;
    return new_factor;
}

static void insert_factor(factor_t **head, int a, int b) {
    factor_t *new_factor = create_factor(a, b);
    if (*head == NULL) {
        *head = new_factor;
    } else {
        factor_t *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_factor;
    }
}

static void free_factors(factor_t *head) {
    factor_t *current = head;
    while (current != NULL) {
        factor_t *next = current->next;
        free(current);
        current = next;
    }
}

product_t *get_palindrome_product(int from, int to) {
    product_t *product = (product_t *)calloc(1, sizeof(product_t));
    if (product == NULL) {
        perror("Failed to allocate memory for product");
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

    for (int i = from; i <= to; ++i) {
        for (int j = i; j <= to; ++j) {
            int candidate = i * j;
            if (is_palindrome(candidate)) {
                if (product->smallest == 0) {
                    product->smallest = candidate;
                    product->largest = candidate;
                    insert_factor(&product->factors_sm, i, j);
                    insert_factor(&product->factors_lg, i, j);
                } else {
                    if (candidate < product->smallest) {
                        free_factors(product->factors_sm);
                        product->factors_sm = NULL;
                        product->smallest = candidate;
                        insert_factor(&product->factors_sm, i, j);
                    } else if (candidate == product->smallest) {
                        insert_factor(&product->factors_sm, i, j);
                    }

                    if (candidate > product->largest) {
                        free_factors(product->factors_lg);
                        product->factors_lg = NULL;
                        product->largest = candidate;
                        insert_factor(&product->factors_lg, i, j);
                    } else if (candidate == product->largest) {
                        insert_factor(&product->factors_lg, i, j);
                    }
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
    assert(p != NULL);

    if (p->factors_lg != NULL) {
        free_factors(p->factors_lg);
    }

    if (p->factors_sm != NULL) {
        free_factors(p->factors_sm);
    }

    free(p);
}