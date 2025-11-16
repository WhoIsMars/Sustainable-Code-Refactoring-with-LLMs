#include "collatz_conjecture.h"
#include <stdexcept>

namespace collatz_conjecture {
    int steps(int num, int step = 0) {
        if (num < 1) {
            throw std::domain_error("Invalid Input");
        }
        while (num != 1) {
            num = (num % 2 == 0) ? (num / 2) : (3 * num + 1);
            ++step;
        }
        return step;
    }
}  // namespace collatz_conjecture