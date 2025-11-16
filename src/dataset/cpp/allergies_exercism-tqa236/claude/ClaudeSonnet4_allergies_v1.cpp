#include "allergies.h"

#include <array>
#include <unordered_set>

namespace allergies {

constexpr std::array<const char*, 8> allergen_names = {
    "eggs", "peanuts", "shellfish", "strawberries",
    "tomatoes", "chocolate", "pollen", "cats"
};

bool allergy_test::is_allergic_to(std::string allergen) {
    return allergies.find(allergen) != allergies.end();
}

std::unordered_set<std::string> allergy_test::get_allergies() {
    if (allergies.empty()) {
        for (int i = 0; i < 8; ++i) {
            if (score & (1 << i)) {
                allergies.insert(allergen_names[i]);
            }
        }
    }
    return allergies;
}

}  // namespace allergies