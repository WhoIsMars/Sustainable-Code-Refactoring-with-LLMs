#include "allergies.h"

#include <unordered_set>
#include <string>
#include <array>

namespace allergies {

static const std::array<std::string, 8> allergen_names = {
    "eggs", "peanuts", "shellfish", "strawberries",
    "tomatoes", "chocolate", "pollen", "cats"
};

bool allergy_test::is_allergic_to(std::string allergen) {
    for (int i = 0; i < 8; ++i) {
        if ((score & (1 << i)) && allergen_names[i] == allergen) {
            return true;
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() {
    std::unordered_set<std::string> result;
    result.reserve(8);
    
    for (int i = 0; i < 8; ++i) {
        if (score & (1 << i)) {
            result.insert(allergen_names[i]);
        }
    }
    
    return result;
}

}