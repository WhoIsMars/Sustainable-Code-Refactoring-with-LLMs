#include "difference_of_squares.h"

namespace difference_of_squares {
	int square_of_sum(int N) {
		int sum = N * (N + 1) / 2;
		return sum * sum;
	}

	int sum_of_squares(int N) {
		return N * (N + 1) * (2 * N + 1) / 6;
	}

	int difference(int N) {
		int sum = N * (N + 1) / 2;
		int squareSum = sum * sum;
		int sumSquares = N * (N + 1) * (2 * N + 1) / 6;
		return squareSum - sumSquares;
	}
}  // namespace difference_of_squares