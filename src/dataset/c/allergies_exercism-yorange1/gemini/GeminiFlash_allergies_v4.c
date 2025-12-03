#include "allergies.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score) {
    return (allergy_score >> allergen) & 1;
}

allergen_list_t get_allergens(uint16_t allergy_score) {
    allergen_list_t list = {0};
    uint8_t count = 0;

    if (allergy_score == 0) {
        return list;
    }

    for (size_t i = 0; i < ALLERGEN_COUNT; ++i) {
        if (allergy_score & (1 << i)) {
            list.allergens[i] = true;
            count++;
        } else {
            list.allergens[i] = false;
        }
    }
    list.count = count;

    return list;
}