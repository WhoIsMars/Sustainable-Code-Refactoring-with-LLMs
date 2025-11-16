#include "difference_of_squares.h"

namespace difference_of_squares {
	int square_of_sum(int N) {		
		long long sum = static_cast<long long>(N) * (N + 1) / 2;
		return static_cast<int>(sum * sum);
	}

	int sum_of_squares(int N) {		
		return static_cast<int>(static_cast<long long>(N) * (N + 1) * (2 * N + 1) / 6);
	}

	int difference(int N) {
		long long sum = static_cast<long long>(N) * (N + 1) / 2;
		long long square_sum = sum * sum;
		long long sum_squares = static_cast<long long>(N) * (N + 1) * (2 * N + 1) / 6;
		return static_cast<int>(square_sum - sum_squares);
	}
}