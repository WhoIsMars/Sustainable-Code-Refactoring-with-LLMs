#include "allergies.h"

namespace allergies {

static const std::array<std::string, 8> allergens{
    "eggs", "peanuts", "shellfish", 
    "strawberries", "tomatoes", "chocolate",
    "pollen", "cats"};

allergy_test::allergy_test(const unsigned int i) : allergy_score(i) {
    calculate_allergies();
}

bool allergy_test::is_allergic_to(const std::string& which) {
    return allergies.count(which) > 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    return allergies;
}

void allergy_test::calculate_allergies() {
    for (std::size_t i = 0; i < allergens.size(); ++i) {
        if (allergy_score & (1u << i)) {
            allergies.emplace(allergens[i]);
        }
    }
}

}  // namespace allergies