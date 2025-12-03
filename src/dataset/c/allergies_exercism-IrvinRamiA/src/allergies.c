#include "allergies.h"
#include <stdio.h>

bool is_allergic_to(allergen_t allergen, uint16_t number)
{
    bool result = false;

    if (number & (1 << allergen))
    {
        result = true;
    }

    return result;
}

allergen_list_t get_allergens(uint16_t number)
{
    allergen_list_t result = {0};

    if (number & (1 << ALLERGEN_EGGS))
    {
        result.count++;
        result.allergens[ALLERGEN_EGGS] = true;
    }
    if (number & (1 << ALLERGEN_PEANUTS))
    {
        result.count++;
        result.allergens[ALLERGEN_PEANUTS] = true;
    }
    if (number & (1 << ALLERGEN_SHELLFISH))
    {
        result.count++;
        result.allergens[ALLERGEN_SHELLFISH] = true;
    }
    if (number & (1 << ALLERGEN_STRAWBERRIES))
    {
        result.count++;
        result.allergens[ALLERGEN_STRAWBERRIES] = true;
    }
    if (number & (1 << ALLERGEN_TOMATOES))
    {
        result.count++;
        result.allergens[ALLERGEN_TOMATOES] = true;
    }
    if (number & (1 << ALLERGEN_CHOCOLATE))
    {
        result.count++;
        result.allergens[ALLERGEN_CHOCOLATE] = true;
    }
    if (number & (1 << ALLERGEN_POLLEN))
    {
        result.count++;
        result.allergens[ALLERGEN_POLLEN] = true;
    }
    if (number & (1 << ALLERGEN_CATS))
    {
        result.count++;
        result.allergens[ALLERGEN_CATS] = true;
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
