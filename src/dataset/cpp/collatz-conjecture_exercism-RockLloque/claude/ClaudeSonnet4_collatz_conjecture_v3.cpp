#include "collatz_conjecture.h"
#include <iostream>
#include <stdexcept>

namespace collatz_conjecture {
    int steps(int num, int step) {
        if (num < 1) {
            throw std::domain_error("Invalid Input");
        }
        
        while (num != 1) {
            if (num & 1) {
                num = 3 * num + 1;
            } else {
                num >>= 1;
            }
            ++step;
        }
        
        return step;
    }
}  // namespace collatz_conjecture