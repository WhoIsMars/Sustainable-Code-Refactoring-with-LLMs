#include "allergies.h"
#include <bitset>

namespace allergies {

static constexpr std::array<const char*, 8> allergens{
    "eggs", "peanuts", "shellfish", 
    "strawberries", "tomatoes", "chocolate",
    "pollen", "cats"
};

allergy_test::allergy_test(const unsigned int i) : allergy_score(i) {
    calculate_allergies();
}

bool allergy_test::is_allergic_to(const std::string& which) const {
    return allergies.count(which) > 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    return allergies;
}

void allergy_test::calculate_allergies() {
    std::bitset<8> score_bits(allergy_score);
    for (std::size_t i = 0; i < allergens.size(); ++i) {
        if (score_bits[i]) {
            allergies.emplace(allergens[i]);
        }
    }
}

}  // namespace allergies