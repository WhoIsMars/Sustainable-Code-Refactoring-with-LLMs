/*
this is a program that practice to use a struct with a member as an array.
Author LK
Date 2025-01-07
*/

#include "allergies.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

bool is_allergic_to(allergen_t allergy_test, int score){
    if (score == 0 || allergy_test >= ALLERGEN_COUNT) {
        return false;
    }
    return (score & (1 << allergy_test)) != 0;
}

allergen_list_t get_allergens(int score){
    allergen_list_t allergens_list = {0, {false, false, false, false, false, false, false, false}};
    
    if (score == 0) {
        return allergens_list;
    }
    
    size_t allergen_count = 0;
    for (size_t i = 0; i < ALLERGEN_COUNT; i++){
        if (score & (1 << i)) {
            allergens_list.allergens[i] = true;
            allergen_count++;
        }
    }
    allergens_list.count = allergen_count;
    
    return allergens_list;
}