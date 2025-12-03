/*
this is a program that practices using a struct with a member as an array.
Author LK
Date 2025-01-07
*/

#include "allergies.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static void int_to_binary(int score, int *array_binary) {
    if (!array_binary) {
        fprintf(stderr, "Error converting integer to binary: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < ALLERGEN_COUNT; i++) {
        array_binary[i] = score & 1;
        score >>= 1;
    }
}

bool is_allergic_to(allergen_t allergy_test, int score) {
    if (allergy_test >= ALLERGEN_COUNT) {
        return false;
    }
    return (score & (1 << allergy_test)) != 0;
}

allergen_list_t get_allergens(int score) {
    allergen_list_t allergens_list = {0, {false, false, false, false, false, false, false, false}};

    for (size_t i = 0; i < ALLERGEN_COUNT; i++) {
        if (score & (1 << i)) {
            allergens_list.allergens[i] = true;
            allergens_list.count++;
        }
    }

    return allergens_list;
}