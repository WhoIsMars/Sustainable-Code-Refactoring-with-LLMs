#include "armstrong_numbers.h"

static int pow1(int x, int n) {
	int res = 1;
	while (n != 0) {
		res = res*x;
		n--;
	}
	return res;
}

bool is_armstrong_number(int candidate) {
	int i, copy, sum;
	i = 0;
	sum = 0;
	copy = candidate;

	for (i = 0; copy > 0; i++) {
		copy /= 10;
	}
	
	copy = candidate;

	while (copy > 0) {
		sum += pow1((copy % 10), i);
		copy /= 10;
	}

	return sum == candidate;
}
