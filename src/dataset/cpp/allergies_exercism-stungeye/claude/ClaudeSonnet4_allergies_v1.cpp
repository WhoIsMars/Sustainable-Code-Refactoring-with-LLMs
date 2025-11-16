#include "allergies.h"

#include <vector>    // std::vector

namespace allergies {
	const std::vector<std::string> allergens{
		"eggs", "peanuts", "shellfish", "strawberries", "tomatoes", "chocolate", "pollen", "cats"
	};

	allergy_test::allergy_test(const int allergy_code) {
		allergies.reserve(8); // Reserve maximum possible size
		
		for (int i = 0; i < 8; ++i) {
			if (allergy_code & (1 << i)) {
				allergies.insert(allergens[i]);
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