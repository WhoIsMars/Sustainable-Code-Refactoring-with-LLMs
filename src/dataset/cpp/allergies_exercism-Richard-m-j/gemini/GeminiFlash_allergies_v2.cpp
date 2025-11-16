#include "allergies.h"
#include <algorithm>

namespace allergies
{
    allergy_test::allergy_test(int score) : allergy_score(score) {}

    bool allergy_test::is_allergic_to(const std::string& allergen) const
    {
        if (allergen == "eggs")
            return (allergy_score & 1) != 0;
        if (allergen == "peanuts")
            return (allergy_score & 2) != 0;
        if (allergen == "shellfish")
            return (allergy_score & 4) != 0;
        if (allergen == "strawberries")
            return (allergy_score & 8) != 0;
        if (allergen == "tomatoes")
            return (allergy_score & 16) != 0;
        if (allergen == "chocolate")
            return (allergy_score & 32) != 0;
        if (allergen == "pollen")
            return (allergy_score & 64) != 0;
        if (allergen == "cats")
            return (allergy_score & 128) != 0;

        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const
    {
        std::unordered_set<std::string> allergies;
        if (is_allergic_to("eggs"))
            allergies.insert("eggs");
        if (is_allergic_to("peanuts"))
            allergies.insert("peanuts");
        if (is_allergic_to("shellfish"))
            allergies.insert("shellfish");
        if (is_allergic_to("strawberries"))
            allergies.insert("strawberries");
        if (is_allergic_to("tomatoes"))
            allergies.insert("tomatoes");
        if (is_allergic_to("chocolate"))
            allergies.insert("chocolate");
        if (is_allergic_to("pollen"))
            allergies.insert("pollen");
        if (is_allergic_to("cats"))
            allergies.insert("cats");
        return allergies;
    }
} // namespace allergies