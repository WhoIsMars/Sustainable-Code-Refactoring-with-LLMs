#include "allergies.h"

#include <vector>    // std::vector
#include <unordered_set> // std::unordered_set

namespace allergies {
	const std::vector<std::string> allergens{
		"eggs", "peanuts", "shellfish", "strawberries", "tomatoes", "chocolate", "pollen", "cats"
	};

	allergy_test::allergy_test(const int allergy_code) {
		for (size_t index = 0; index < allergens.size(); ++index) {
			if (allergy_code & (1 << index)) {
				allergies.insert(allergens[index]);
			}
		}
	}

	bool allergy_test::is_allergic_to(const std::string& potential_allergen) const {
		return allergies.find(potential_allergen) != allergies.end();
	}

	std::unordered_set<std::string> allergy_test::get_allergies() const {
		return allergies;
	}

} // namespace allergies