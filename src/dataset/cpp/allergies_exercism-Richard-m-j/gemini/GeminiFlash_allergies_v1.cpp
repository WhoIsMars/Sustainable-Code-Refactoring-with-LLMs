#include "allergies.h"

#include <array>

namespace allergies {

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    if (allergen == "eggs") return (allergy_score & 1) != 0;
    if (allergen == "peanuts") return (allergy_score & 2) != 0;
    if (allergen == "shellfish") return (allergy_score & 4) != 0;
    if (allergen == "strawberries") return (allergy_score & 8) != 0;
    if (allergen == "tomatoes") return (allergy_score & 16) != 0;
    if (allergen == "chocolate") return (allergy_score & 32) != 0;
    if (allergen == "pollen") return (allergy_score & 64) != 0;
    if (allergen == "cats") return (allergy_score & 128) != 0;
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> allergies;
    if (allergy_score & 1) allergies.insert("eggs");
    if (allergy_score & 2) allergies.insert("peanuts");
    if (allergy_score & 4) allergies.insert("shellfish");
    if (allergy_score & 8) allergies.insert("strawberries");
    if (allergy_score & 16) allergies.insert("tomatoes");
    if (allergy_score & 32) allergies.insert("chocolate");
    if (allergy_score & 64) allergies.insert("pollen");
    if (allergy_score & 128) allergies.insert("cats");
    return allergies;
}

allergy_test::allergy_test(int score) : allergy_score(score) {}

}  // namespace allergies