#include "sum_of_multiples.h"

namespace sum_of_multiples {
	int to(vector<int> numbers, int upper) {
		set<int> multiples;
		for (int i : numbers) {
			for (int j = i; j < upper; j += i) {
				multiples.insert(j);
			}
		}
		return accumulate(multiples.begin(), multiples.end(), 0);
	}
}  // namespace sum_of_multiples
