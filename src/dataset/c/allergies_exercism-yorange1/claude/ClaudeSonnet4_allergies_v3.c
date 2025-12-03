#include "allergies.h"

#include <stddef.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score)
{
    return (allergy_score & (1U << allergen)) != 0;
}

allergen_list_t get_allergens(uint16_t allergy_score)
{
    allergen_list_t list = {0};
    uint16_t masked_score = allergy_score & ((1U << ALLERGEN_COUNT) - 1);
    
    for (size_t i = 0; masked_score && i < ALLERGEN_COUNT; i++)
    {
        if (masked_score & 1U)
        {
            list.allergens[i] = true;
            list.count++;
        }
        masked_score >>= 1;
    }

    return list;
}