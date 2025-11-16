#include "difference_of_squares.h"

namespace difference_of_squares {
	int square_of_sum(int N) {		
		return (int)pow(N * (N + 1) / 2, 2);
	}

	//Sum of square of 1 to N = (2 * N + 1) * (N + 1) * N / 6
	int sum_of_squares(int N) {		
		return (int)((2 * N + 1) * (N + 1) * N / 6);
	}

	int difference(int N) {
		return square_of_sum(N) - sum_of_squares(N);
	}
}  // namespace difference_of_squares
