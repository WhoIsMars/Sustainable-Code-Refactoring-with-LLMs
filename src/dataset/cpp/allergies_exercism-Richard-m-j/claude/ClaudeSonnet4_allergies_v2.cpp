#include "allergies.h"

namespace allergies
{
    bool allergy_test::is_allergic_to(std::string allergen)
    {
        static const std::unordered_map<std::string, int> allergen_bits = {
            {"eggs", 0}, {"peanuts", 1}, {"shellfish", 2}, {"strawberries", 3},
            {"tomatoes", 4}, {"chocolate", 5}, {"pollen", 6}, {"cats", 7}
        };
        
        auto it = allergen_bits.find(allergen);
        if (it == allergen_bits.end()) {
            return false;
        }
        
        return (allergy_score & (1 << it->second)) != 0;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        static const std::array<std::string, 8> allergen_names = {
            "eggs", "peanuts", "shellfish", "strawberries",
            "tomatoes", "chocolate", "pollen", "cats"
        };
        
        std::unordered_set<std::string> allergies;
        
        for (int i = 0; i < 8; ++i) {
            if (allergy_score & (1 << i)) {
                allergies.insert(allergen_names[i]);
            }
        }
        
        return allergies;
    }

    allergy_test::allergy_test(int score)
    {
        allergy_score = score;
    }
} // namespace allergies