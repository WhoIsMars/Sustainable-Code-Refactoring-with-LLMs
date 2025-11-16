#include "allergies.h"

allergies::allergy_test::allergy_test(allergies::ushort score) : score(score & 0xff) {
    for (size_t i = 0; i < ALLERGENS.size(); ++i) {
        if (score & (1 << i)) {
            allergies.emplace(ALLERGENS[i]);
        }
    }
}

bool allergies::allergy_test::is_allergic_to(const std::string &allergen) const noexcept {
    return allergies.find(allergen) != allergies.end();
}

allergies::allergies_t allergies::allergy_test::get_allergies() const {
    return allergies;
}