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
        if (number & (1 << allergen))
        {
            result.allergens[allergen] = true;
            result.count++;
        }
    }
    
    return result;
}

/*
The list of items (and their value) that were tested are:

    eggs (1)
    peanuts (2)
    shellfish (4)
    strawberries (8)
    tomatoes (16)
    chocolate (32)
    pollen (64)
    cats (128)
*/