/**
 * Given a person's allergy score, determine whether or not they're allergic to
 * a specific allergy and their full list of allergies.
 */

#include "allergies.h"

using std::string;
using std::unordered_set;

namespace allergies {
    constexpr const char* allergy_names[] {
        "eggs",
        "peanuts",
        "shellfish",
        "strawberries",
        "tomatoes",
        "chocolate",
        "pollen",
        "cats"
    };

    constexpr size_t allergy_names_size = sizeof(allergy_names) / sizeof(allergy_names[0]);

    allergy_test::allergy_test(int score_value) : score(score_value) {
        for (size_t i = 0; i < allergy_names_size; ++i) {
            if (score & (1 << i)) {
                allergy_set.insert(allergy_names[i]);
            }
        }
    }

    bool allergy_test::is_allergic_to(const string& allergy_name) const {
        return allergy_set.find(allergy_name) != allergy_set.end();
    }

    unordered_set<string> allergy_test::get_allergies() const {
        return allergy_set;
    }
}  // namespace allergies