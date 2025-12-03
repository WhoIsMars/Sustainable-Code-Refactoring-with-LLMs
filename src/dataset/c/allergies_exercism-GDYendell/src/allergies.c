#include "allergies.h"

bool is_allergic_to(allergen_t allergen, int score) {
    return score >> allergen & 1;
}

allergen_list_t get_allergens(int score) {
    allergen_list_t allergens;
    allergens.count = 0;

    for (int i = 0; i < ALLERGEN_COUNT; ++i) {
        if (is_allergic_to(i, score)) {
            allergens.allergens[i] = true;
            ++allergens.count;
        } else {
            allergens.allergens[i] = false;
        }
    }

    return allergens;
}
