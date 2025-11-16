#include "sum_of_multiples.h"

#include <numeric>
#include <unordered_set>

namespace sum_of_multiples {

	int to(const std::vector<int>& factors, const int exclusive_upper_bound) {
		if (exclusive_upper_bound <= 1) {
			return 0;
		}

		std::unordered_set<int> multiples;
		for (int factor : factors) {
			if (factor > 0) {
				for (int i = factor; i < exclusive_upper_bound; i += factor) {
					multiples.insert(i);
				}
			}
		}

		return std::accumulate(multiples.begin(), multiples.end(), 0);
	}
} // namespace sum_of_multiples