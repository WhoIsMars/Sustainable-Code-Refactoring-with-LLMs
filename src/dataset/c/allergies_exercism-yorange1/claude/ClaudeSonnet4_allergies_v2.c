#include "allergies.h"

#include <stddef.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score)
{
    return (allergy_score >> (int)allergen) & 1;
}

allergen_list_t get_allergens(uint16_t allergy_score)
{
    allergen_list_t list = {0};
    uint16_t score = allergy_score;
    
    for (size_t i = 0; i < ALLERGEN_COUNT && score; i++)
    {
        if (score & 1)
        {
            list.allergens[i] = true;
            list.count++;
        }
        score >>= 1;
    }

    return list;
}