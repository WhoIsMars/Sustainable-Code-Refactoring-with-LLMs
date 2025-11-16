#include "allergies.h"

#include <vector>
#include <string>

namespace allergies {
	static constexpr const char* allergen_names[] = {
		"eggs", "peanuts", "shellfish", "strawberries", "tomatoes", "chocolate", "pollen", "cats"
	};
	static constexpr int num_allergens = 8;

	allergy_test::allergy_test(const int allergy_code) {
		allergies.reserve(num_allergens);
		for (int i = 0; i < num_allergens; ++i) {
			if (allergy_code & (1 << i)) {
				allergies.emplace(allergen_names[i]);
			}
		}
	}

	bool allergy_test::is_allergic_to(const std::string& potential_allergen) const {
		return allergies.count(potential_allergen) == 1;
	}

	std::unordered_set<std::string> allergy_test::get_allergies() const {
		return allergies;
	}

} // namespace allergies