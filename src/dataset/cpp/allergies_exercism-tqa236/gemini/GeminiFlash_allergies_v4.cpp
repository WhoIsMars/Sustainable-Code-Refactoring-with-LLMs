#include "allergies.h"

#include <algorithm>
#include <bitset>
#include <map>
#include <unordered_set>

namespace allergies {

const std::map<int, std::string> allergen_value = {
    {1, "eggs"},      {2, "peanuts"},    {4, "shellfish"}, {8, "strawberries"},
    {16, "tomatoes"}, {32, "chocolate"}, {64, "pollen"},   {128, "cats"}};

allergy_test::allergy_test(int score) : score(score) {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
  return allergies.count(allergen) > 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() {
  allergies.clear();
  int remaining_score = score;
  for (const auto& pair : allergen_value) {
    if (remaining_score >= pair.first) {
      if ((score & pair.first) != 0) {
        allergies.insert(pair.second);
      }
    }
  }
  return allergies;
}

}  // namespace allergies