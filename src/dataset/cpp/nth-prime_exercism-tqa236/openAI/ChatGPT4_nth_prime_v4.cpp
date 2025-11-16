#include "nth_prime.h"

#include <cmath>
#include <stdexcept>
#include <vector>

int nth_prime::nth(int number) {
    if (number <= 0) {
        throw std::domain_error("Weird case.");
    }

    if (number == 1) {
        return 2;
    }

    int upper_bound = static_cast<int>(number * (std::log(number) + std::log(std::log(number)))) + 10;
    std::vector<bool> is_prime(upper_bound + 1, true);
    is_prime[0] = is_prime[1] = false;

    int count = 0;
    for (int i = 2; i <= upper_bound; ++i) {
        if (is_prime[i]) {
            ++count;
            if (count == number) {
                return i;
            }
            for (int j = i * 2; j <= upper_bound; j += i) {
                is_prime[j] = false;
            }
        }
    }

    throw std::runtime_error("Prime number not found within calculated bounds.");
}