#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <stdbool.h>

typedef enum {
   ALLERGEN_EGGS = 0,
   ALLERGEN_PEANUTS,
   ALLERGEN_SHELLFISH,
   ALLERGEN_STRAWBERRIES,
   ALLERGEN_TOMATOES,
   ALLERGEN_CHOCOLATE,
   ALLERGEN_POLLEN,
   ALLERGEN_CATS,
   ALLERGEN_COUNT,
} allergen_t;

typedef struct {
   int count;
   bool allergens[ALLERGEN_COUNT];
} allergen_list_t;

//L.K added 2024-12-22
bool is_allergic_to(allergen_t allergy_test,int score);
allergen_list_t get_allergens(int score);
int int_to_binary(int score, int *array_binary);

#endif
