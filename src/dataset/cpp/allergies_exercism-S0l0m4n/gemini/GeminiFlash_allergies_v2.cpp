/**
 * Given a person's allergy score, determine whether or not they're allergic to
 * a specific allergy and their full list of allergies.
 */

#include "allergies.h"

#include <array>
#include <algorithm>

using std::string;
using std::unordered_set;
using std::array;

namespace allergies {
    constexpr std::array<const char*, 8> allergy_names {
        "eggs",
        "peanuts",
        "shellfish",
        "strawberries",
        "tomatoes",
        "chocolate",
        "pollen",
        "cats"
    };

    allergy_test::allergy_test(int score_value) : score(score_value) {
        int remaining_score = score_value;
        for (size_t i = 0; i < allergy_names.size(); ++i) {
            int allergy_value = 1 << i;
            if (remaining_score >= allergy_value) {
                if (score_value & allergy_value) {
                    allergy_set.insert(allergy_names[i]);
                    remaining_score -= allergy_value;
                }
            } else {
                break; // Optimization: No need to check further if allergy_value exceeds remaining_score
            }
        }
    }

    bool allergy_test::is_allergic_to(const string& allergy_name) const {
        return allergy_set.count(allergy_name) > 0;
    }

    unordered_set<string> allergy_test::get_allergies() const {
        return allergy_set;
    }
}  // namespace allergies