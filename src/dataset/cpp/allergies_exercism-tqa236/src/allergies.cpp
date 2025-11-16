#include "allergies.h"

#include <math.h>

#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
using namespace std;

namespace allergies {
map<int, string> allergen_value = {
    {1, "eggs"},      {2, "peanuts"},    {4, "shellfish"}, {8, "strawberries"},
    {16, "tomatoes"}, {32, "chocolate"}, {64, "pollen"},   {128, "cats"}};
bool allergy_test::is_allergic_to(string allergen) {
  return allergies.find(allergen) != allergies.end();
}
unordered_set<string> allergy_test::get_allergies() {
  string binary_score = bitset<8>(score).to_string();
  reverse(binary_score.begin(), binary_score.end());
  for (unsigned int i = 0; i < binary_score.size(); i++) {
    if (binary_score[i] == '1') {
      allergies.insert(allergen_value[round(pow(2, i))]);
    }
  }
  return allergies;
}
}  // namespace allergies
