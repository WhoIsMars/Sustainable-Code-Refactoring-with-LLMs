#include "allergies.h"
#include <stdbool.h>
#include <stdio.h>

bool is_allergic_to(allergen_t allergy, int score) {
  return (score & (1 << allergy)) != 0;
}

allergen_list_t get_allergens(int score) {
  allergen_list_t allergens_list = {0, {false}};
  int allergen_count = 0;

  for (size_t i = 0; i < ALLERGEN_COUNT; ++i) {
    if (score & (1 << i)) {
      allergens_list.allergens[i] = true;
      allergen_count++;
    } else {
      allergens_list.allergens[i] = false;
    }
  }

  allergens_list.count = allergen_count;
  return allergens_list;
}