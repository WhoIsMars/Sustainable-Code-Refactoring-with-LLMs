#include "allergies.h"

namespace allergies
{
    static constexpr std::array<std::string_view, 8> allergen_names = {
        "eggs", "peanuts", "shellfish", "strawberries",
        "tomatoes", "chocolate", "pollen", "cats"
    };

    bool allergy_test::is_allergic_to(std::string allergen)
    {
        for (int i = 0; i < 8; ++i) {
            if (allergen == allergen_names[i]) {
                return (allergy_score & (1 << i)) != 0;
            }
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        std::unordered_set<std::string> allergies;
        allergies.reserve(8);
        
        for (int i = 0; i < 8; ++i) {
            if (allergy_score & (1 << i)) {
                allergies.emplace(allergen_names[i]);
            }
        }
        return allergies;
    }

    allergy_test::allergy_test(int score) : allergy_score(score)
    {
    }
}