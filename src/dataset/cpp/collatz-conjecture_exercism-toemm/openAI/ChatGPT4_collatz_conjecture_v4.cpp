#include "collatz_conjecture.h"
#include <stdexcept>

namespace collatz_conjecture {

int steps(int i) {
    if (i <= 0) throw std::domain_error("i must be positive");

    int ctr = 0;
    while (i > 1) {
        i = (i % 2 == 0) ? (i / 2) : (i * 3 + 1);
        ++ctr;
    }
    return ctr;
}

}  // namespace collatz_conjecture