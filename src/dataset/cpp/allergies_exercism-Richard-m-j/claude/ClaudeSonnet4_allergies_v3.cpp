#include "allergies.h"

namespace allergies
{
    static constexpr int ALLERGEN_COUNT = 8;
    static constexpr const char* ALLERGEN_NAMES[ALLERGEN_COUNT] = {
        "eggs", "peanuts", "shellfish", "strawberries",
        "tomatoes", "chocolate", "pollen", "cats"
    };

    bool allergy_test::is_allergic_to(std::string allergen)
    {
        for (int i = 0; i < ALLERGEN_COUNT; ++i) {
            if (allergen == ALLERGEN_NAMES[i]) {
                return (allergy_score & (1 << i)) != 0;
            }
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        std::unordered_set<std::string> allergies;
        allergies.reserve(ALLERGEN_COUNT);
        
        for (int i = 0; i < ALLERGEN_COUNT; ++i) {
            if (allergy_score & (1 << i)) {
                allergies.insert(ALLERGEN_NAMES[i]);
            }
        }
        return allergies;
    }

    allergy_test::allergy_test(int score)
    {
        allergy_score = score;
    }
}