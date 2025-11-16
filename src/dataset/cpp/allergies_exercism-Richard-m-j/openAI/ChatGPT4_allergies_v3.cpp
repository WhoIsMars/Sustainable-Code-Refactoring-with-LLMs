#include "allergies.h"
#include <bitset>

namespace allergies
{
    bool allergy_test::is_allergic_to(std::string allergen)
    {
        static const std::unordered_map<std::string, int> allergen_map = {
            {"eggs", 0}, {"peanuts", 1}, {"shellfish", 2}, {"strawberries", 3},
            {"tomatoes", 4}, {"chocolate", 5}, {"pollen", 6}, {"cats", 7}};
        
        auto it = allergen_map.find(allergen);
        if (it != allergen_map.end())
        {
            return (allergy_score & (1 << it->second)) != 0;
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        static const std::vector<std::string> allergens = {
            "eggs", "peanuts", "shellfish", "strawberries",
            "tomatoes", "chocolate", "pollen", "cats"};
        
        std::unordered_set<std::string> allergies;
        for (size_t i = 0; i < allergens.size(); ++i)
        {
            if (allergy_score & (1 << i))
            {
                allergies.insert(allergens[i]);
            }
        }
        return allergies;
    }

    allergy_test::allergy_test(int score) : allergy_score(score & 255) {}
} // namespace allergies