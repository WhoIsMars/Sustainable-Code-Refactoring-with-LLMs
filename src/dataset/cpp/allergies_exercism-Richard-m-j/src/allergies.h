#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <string>
#include <unordered_set>

namespace allergies
{
    class allergy_test
    {
    public:
        bool is_allergic_to(std::string allergen);
        std::unordered_set<std::string> get_allergies();
        allergy_test(int score);
        int allergy_score;
    };
} // namespace allergies

#endif // ALLERGIES_H
