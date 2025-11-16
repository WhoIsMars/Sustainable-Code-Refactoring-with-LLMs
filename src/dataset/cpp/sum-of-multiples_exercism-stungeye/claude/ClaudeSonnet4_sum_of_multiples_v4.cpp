#include "sum_of_multiples.h"

#include <algorithm>
#include <unordered_set>

namespace sum_of_multiples {

	int to(const std::vector<int>& factors, const int exclusive_upper_bound) {
		if (factors.empty() || exclusive_upper_bound <= 1) {
			return 0;
		}

		std::unordered_set<int> valid_factors;
		for (const auto factor : factors) {
			if (factor > 0 && factor < exclusive_upper_bound) {
				valid_factors.insert(factor);
			}
		}

		if (valid_factors.empty()) {
			return 0;
		}

		std::unordered_set<int> multiples;
		for (const auto factor : valid_factors) {
			for (int multiple = factor; multiple < exclusive_upper_bound; multiple += factor) {
				multiples.insert(multiple);
			}
		}

		int sum = 0;
		for (const auto multiple : multiples) {
			sum += multiple;
		}

		return sum;
	}
} // namespace sum_of_multiples