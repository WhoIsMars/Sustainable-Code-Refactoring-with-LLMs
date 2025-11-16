#include "allergies.h"

#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

namespace allergies {
const unordered_map<int, std::string> allergen_value = {
    {1, "eggs"},      {2, "peanuts"},    {4, "shellfish"}, {8, "strawberries"},
    {16, "tomatoes"}, {32, "chocolate"}, {64, "pollen"},   {128, "cats"}};

bool allergy_test::is_allergic_to(const std::string& allergen) const {
  return allergies.count(allergen) > 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() {
  if (allergies.empty()) {
    for (const auto& [value, name] : allergen_value) {
      if (score & value) {
        allergies.insert(name);
      }
    }
  }
  return allergies;
}
}  // namespace allergies