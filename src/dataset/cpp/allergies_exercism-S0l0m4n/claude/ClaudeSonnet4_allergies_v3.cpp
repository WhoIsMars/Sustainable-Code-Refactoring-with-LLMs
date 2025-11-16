/**
 * Given a person's allergy score, determine whether or not they're allergic to
 * a specific allergy and their full list of allergies.
 */

#include "allergies.h"
#include <array>

using std::string;
using std::unordered_set;

namespace allergies {
    constexpr std::array<const char*, 8> allergy_names {{
        "eggs",
        "peanuts",
        "shellfish",
        "strawberries",
        "tomatoes",
        "chocolate",
        "pollen",
        "cats"
    }};

    allergy_test::allergy_test(int score_value) : score(score_value & 0xFF) {
        allergy_set.reserve(8);
        for (int i = 0; i < 8; ++i) {
            if (score & (1 << i)) {
                allergy_set.emplace(allergy_names[i]);
            }
        }
    }

    bool allergy_test::is_allergic_to(string allergy_name) {
        return allergy_set.find(allergy_name) != allergy_set.end();
    }

    unordered_set<string> allergy_test::get_allergies() {
        return allergy_set;
    }
}  // namespace allergies