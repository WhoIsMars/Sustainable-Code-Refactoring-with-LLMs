#include "allergies.h"
#include <unordered_map>

namespace allergies
{
    namespace
    {
        const std::unordered_map<std::string, int> allergen_map = {
            {"eggs", 1},
            {"peanuts", 2},
            {"shellfish", 4},
            {"strawberries", 8},
            {"tomatoes", 16},
            {"chocolate", 32},
            {"pollen", 64},
            {"cats", 128}};
    }

    bool allergy_test::is_allergic_to(std::string allergen)
    {
        auto it = allergen_map.find(allergen);
        if (it != allergen_map.end())
        {
            return (allergy_score & it->second) != 0;
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        std::unordered_set<std::string> allergies;
        for (const auto &pair : allergen_map)
        {
            if ((allergy_score & pair.second) != 0)
            {
                allergies.insert(pair.first);
            }
        }
        return allergies;
    }

    allergy_test::allergy_test(int score) : allergy_score(score & 255) {}
} // namespace allergies