#include "armstrong_numbers.h"

static int fast_pow(int x, int n) {
	int res = 1;
	while (n > 0) {
		if (n % 2 == 1) {
			res *= x;
		}
		x *= x;
		n /= 2;
	}
	return res;
}

bool is_armstrong_number(int candidate) {
	int copy = candidate, sum = 0, digits[10], i = 0;

	while (copy > 0) {
		digits[i++] = copy % 10;
		copy /= 10;
	}

	for (int j = 0; j < i; j++) {
		sum += fast_pow(digits[j], i);
		if (sum > candidate) {
			return false; // Early exit if sum exceeds candidate
		}
	}

	return sum == candidate;
}