#include "allergies.h"

allergies::allergy_test::allergy_test(allergies::ushort score) : score(score & 0xff) {
    allergies.reserve(8); // Reserve space for maximum possible allergens
    const auto allergen_count = static_cast<int>(ALLERGENS.size());
    for (int i = 0; i < allergen_count; ++i) {
        if ((1 << i) & this->score) {
            allergies.insert(ALLERGENS[i]); 
        }
    }
}

bool allergies::allergy_test::is_allergic_to(const std::string &allergen) noexcept {
    return allergies.find(allergen) != allergies.end();
}

allergies::allergies_t allergies::allergy_test::get_allergies() const {
    return allergies;
}