#include "allergies.h"

bool is_allergic_to(allergen_t allergen, int score) {
    return (score >> allergen) & 1;
}

allergen_list_t get_allergens(int score) {
    allergen_list_t allergens = {0};
    
    for (int i = 0; i < ALLERGEN_COUNT; ++i) {
        allergens.allergens[i] = (score >> i) & 1;
        allergens.count += allergens.allergens[i];
    }

    return allergens;
}