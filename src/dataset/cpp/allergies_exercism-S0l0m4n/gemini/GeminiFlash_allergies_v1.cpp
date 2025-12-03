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
        // Precompute the valid score range to avoid unnecessary iterations.
        int valid_score = score % (1 << allergy_names.size());

        for (size_t i = 0; i < allergy_names.size(); ++i) {
            if (valid_score & (1 << i)) {
                allergy_set.insert(allergy_names[i]);
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