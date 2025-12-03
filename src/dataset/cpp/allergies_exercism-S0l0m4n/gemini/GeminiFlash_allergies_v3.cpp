/**
 * Given a person's allergy score, determine whether or not they're allergic to
 * a specific allergy and their full list of allergies.
 */

#include "allergies.h"

#include <algorithm>
#include <array>
#include <numeric>

using std::string;
using std::unordered_set;

namespace allergies {

    constexpr std::array<const char*, 8> allergy_names = {
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
            int allergy_score = 1 << i;
            if (remaining_score >= allergy_score) {
                if (remaining_score & allergy_score) {
                    allergy_set.insert(allergy_names[i]);
                    remaining_score -= allergy_score;
                }
            } else {
                break; // Optimization: No need to check further if allergy_score exceeds remaining_score
            }
        }
    }

    bool allergy_test::is_allergic_to(string allergy_name) {
        return allergy_set.count(allergy_name) > 0;
    }

    unordered_set<string> allergy_test::get_allergies() {
        return allergy_set;
    }
}  // namespace allergies