#include "allergies.h"

#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

namespace allergies {
const unordered_map<int, string> allergen_value = {
    {1, "eggs"},      {2, "peanuts"},    {4, "shellfish"}, {8, "strawberries"},
    {16, "tomatoes"}, {32, "chocolate"}, {64, "pollen"},   {128, "cats"}};

bool allergy_test::is_allergic_to(const string& allergen) const {
  return allergies.count(allergen) > 0;
}

unordered_set<string> allergy_test::get_allergies() {
  if (!allergies.empty()) return allergies;  // Avoid recomputation if already populated
  for (const auto& [value, name] : allergen_value) {
    if (score & value) {
      allergies.insert(name);
    }
  }
  return allergies;
}
}  // namespace allergies