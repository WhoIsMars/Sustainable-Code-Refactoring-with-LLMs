#include "sum_of_multiples.h"

#include <unordered_set>

namespace sum_of_multiples {

	int to(const std::vector<int>& factors, const int exclusive_upper_bound) {
		if (factors.empty() || exclusive_upper_bound <= 1) {
			return 0;
		}

		std::unordered_set<int> multiples;

		for (const auto factor : factors) {
			if (factor <= 0) continue;
			for (int i = factor; i < exclusive_upper_bound; i += factor) {
				multiples.insert(i);
			}
		}

		int sum = 0;
		for (const auto multiple : multiples) {
			sum += multiple;
		}

		return sum;
	}
} // namespace sum_of_multiples