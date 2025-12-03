#include "allergies.h"

#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace allergies {

const std::map<int, std::string> allergen_value = {
    {1, "eggs"},      {2, "peanuts"},    {4, "shellfish"}, {8, "strawberries"},
    {16, "tomatoes"}, {32, "chocolate"}, {64, "pollen"},   {128, "cats"}};

allergy_test::allergy_test(int score) : score(score) {
  // Precompute allergies during construction
  for (const auto& pair : allergen_value) {
    if ((score & pair.first) != 0) {
      allergies.insert(pair.second);
    }
  }
}

bool allergy_test::is_allergic_to(const string& allergen) const {
  return allergies.count(allergen) > 0;
}

unordered_set<string> allergy_test::get_allergies() const { return allergies; }

}  // namespace allergies