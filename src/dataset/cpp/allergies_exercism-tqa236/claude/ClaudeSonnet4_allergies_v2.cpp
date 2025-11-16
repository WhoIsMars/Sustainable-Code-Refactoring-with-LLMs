#include "allergies.h"

#include <unordered_set>
using namespace std;

namespace allergies {
static const string allergen_names[8] = {
    "eggs", "peanuts", "shellfish", "strawberries",
    "tomatoes", "chocolate", "pollen", "cats"
};

bool allergy_test::is_allergic_to(string allergen) {
  if (allergies.empty()) {
    get_allergies();
  }
  return allergies.find(allergen) != allergies.end();
}

unordered_set<string> allergy_test::get_allergies() {
  if (!allergies.empty()) {
    return allergies;
  }
  
  int masked_score = score & 0xFF;
  for (int i = 0; i < 8; i++) {
    if (masked_score & (1 << i)) {
      allergies.insert(allergen_names[i]);
    }
  }
  return allergies;
}
}  // namespace allergies