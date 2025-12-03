#include "allergies.h"

#include <stddef.h>
#include <stdint.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score)
{
    return (allergy_score & (1U << allergen)) != 0;
}

allergen_list_t get_allergens(uint16_t allergy_score)
{
    allergen_list_t list = {0};

    uint16_t mask = allergy_score;
    for (size_t i = 0; mask && i < ALLERGEN_COUNT; i++, mask >>= 1)
    {
        if (mask & 1)
        {
            list.allergens[i] = true;
            list.count++;
        }
    }

    return list;
}