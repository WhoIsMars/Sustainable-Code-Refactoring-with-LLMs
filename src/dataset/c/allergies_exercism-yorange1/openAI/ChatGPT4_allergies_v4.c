#include "allergies.h"

#include <stddef.h>
#include <stdint.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score)
{
    return (allergy_score & (1U << allergen)) != 0;
}

allergen_list_t get_allergens(uint16_t allergy_score)
{
    allergen_list_t list = { .allergens = {false}, .count = 0 };

    for (size_t i = 0; i < ALLERGEN_COUNT; i++)
    {
        if (allergy_score & (1U << i))
        {
            list.allergens[i] = true;
            list.count++;
        }
    }

    return list;
}