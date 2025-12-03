#include "allergies.h"

#include <stddef.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score)
{
    return (allergy_score & (1 << (int)allergen)) != 0;
}

allergen_list_t get_allergens(uint16_t allergy_score)
{
    allergen_list_t list = {0};
    uint16_t score = allergy_score & ((1 << ALLERGEN_COUNT) - 1);
    
    for (size_t i = 0; score && i < ALLERGEN_COUNT; i++)
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