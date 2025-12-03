#include "allergies.h"
#include <stdio.h>

bool is_allergic_to(allergen_t allergen, uint16_t number)
{
    return (number & (1 << allergen)) != 0;
}

allergen_list_t get_allergens(uint16_t number)
{
    allergen_list_t result = {0};

    for (allergen_t allergen = ALLERGEN_EGGS; allergen <= ALLERGEN_CATS; allergen++)
    {
        if (is_allergic_to(allergen, number))
        {
            result.allergens[allergen] = true;
            result.count++;
        }
    }

    return result;
}