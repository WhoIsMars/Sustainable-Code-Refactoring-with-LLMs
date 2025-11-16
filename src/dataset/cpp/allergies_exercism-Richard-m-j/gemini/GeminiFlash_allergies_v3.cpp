#include "allergies.h"
#include <array>

namespace allergies
{
    bool allergy_test::is_allergic_to(std::string allergen)
    {
        static const std::unordered_map<std::string, int> allergen_scores = {
            {"eggs", 1},
            {"peanuts", 2},
            {"shellfish", 4},
            {"strawberries", 8},
            {"tomatoes", 16},
            {"chocolate", 32},
            {"pollen", 64},
            {"cats", 128}};

        auto it = allergen_scores.find(allergen);
        if (it != allergen_scores.end())
        {
            return (allergy_score & it->second) != 0;
        }

        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        std::unordered_set<std::string> allergies;
        static const std::array<std::string, 8> allergens = {
            "eggs", "peanuts", "shellfish", "strawberries", "tomatoes", "chocolate", "pollen", "cats"};

        static const std::array<int, 8> allergen_scores = {1, 2, 4, 8, 16, 32, 64, 128};

        for (size_t i = 0; i < allergens.size(); ++i)
        {
            if ((allergy_score & allergen_scores[i]) != 0)
            {
                allergies.insert(allergens[i]);
            }
        }
        return allergies;
    }

    allergy_test::allergy_test(int score)
    {
        allergy_score = score;
    }
} // namespace allergies