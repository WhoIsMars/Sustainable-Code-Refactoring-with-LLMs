#include "allergies.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace allergies {

const std::array<std::pair<int, std::string>, 8> allergen_values = {
    {{1, "eggs"},
     {2, "peanuts"},
     {4, "shellfish"},
     {8, "strawberries"},
     {16, "tomatoes"},
     {32, "chocolate"},
     {64, "pollen"},
     {128, "cats"}}};

allergy_test::allergy_test(int score) : score(score) {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
  return allergies.count(allergen) > 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() {
  if (!allergies.empty()) {
    return allergies; // Return cached allergies if already computed
  }

  for (const auto& allergen : allergen_values) {
    if (score & allergen.first) {
      allergies.insert(allergen.second);
    }
  }
  return allergies;
}

} // namespace allergies