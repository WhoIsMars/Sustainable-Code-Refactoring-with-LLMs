#include "allergies.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int int_to_binary(int score, int *array_binary) {
    if (!array_binary) {
        fprintf(stderr, "error when convert integer to binary-description %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < 64; i++) {
        array_binary[i] = score & 1;
        score >>= 1;
        if (score == 0) break;
    }

    return 1;
}

bool is_allergic_to(allergen_t allergy_test, int score) {
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