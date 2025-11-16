#include "allergies.h"

allergies::allergy_test::allergy_test(allergies::ushort score) : score(score & 0xff) {
    allergies.reserve(8); // Reserve space for maximum possible allergens
    for (int i = 0; i < static_cast<int>(ALLERGENS.size()); i++) {
        if ((1 << i) & this->score) {
            allergies.emplace(ALLERGENS[i]);
        }
    }
}

bool allergies::allergy_test::is_allergic_to(const std::string &allergen) noexcept {
    return allergies.find(allergen) != allergies.end();
}

allergies::allergies_t allergies::allergy_test::get_allergies() const {
    return allergies;
}