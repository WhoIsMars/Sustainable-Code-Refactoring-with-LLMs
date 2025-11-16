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

    const array<string, 8> allergy_names {
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
        for (size_t i = 0; i < allergy_names.size(); ++i) {
            if (score_value & (1 << i)) {
                allergy_set.insert(allergy_names[i]);
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