#include "allergies.h"

#include <vector>
#include <string>

namespace allergies {
	constexpr const char* allergen_names[] = {
		"eggs", "peanuts", "shellfish", "strawberries", "tomatoes", "chocolate", "pollen", "cats"
	};
	constexpr size_t num_allergens = sizeof(allergen_names) / sizeof(allergen_names[0]);

	allergy_test::allergy_test(const int allergy_code) : code(allergy_code & 0xFF) {
	}

	bool allergy_test::is_allergic_to(const std::string& potential_allergen) const {
		for (size_t i = 0; i < num_allergens; ++i) {
			if (potential_allergen == allergen_names[i]) {
				return (code & (1 << i)) != 0;
			}
		}
		return false;
	}

	std::unordered_set<std::string> allergy_test::get_allergies() const {
		std::unordered_set<std::string> result;
		result.reserve(num_allergens);
		
		for (size_t i = 0; i < num_allergens; ++i) {
			if (code & (1 << i)) {
				result.emplace(allergen_names[i]);
			}
		}
		return result;
	}

} // namespace allergies