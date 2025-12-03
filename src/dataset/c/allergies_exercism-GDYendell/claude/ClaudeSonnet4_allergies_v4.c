#include "allergies.h"

bool is_allergic_to(allergen_t allergen, int score) {
    return (score >> allergen) & 1;
}

allergen_list_t get_allergens(int score) {
    allergen_list_t allergens = {0};
    
    const int masked_score = score & ((1 << ALLERGEN_COUNT) - 1);
    allergens.count = __builtin_popcount(masked_score);
    
    for (int i = 0; i < ALLERGEN_COUNT; ++i) {
        allergens.allergens[i] = (masked_score >> i) & 1;
    }
    
    return allergens;
}