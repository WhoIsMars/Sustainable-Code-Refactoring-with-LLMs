#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {

int steps(int i) {
    if (i <= 0) throw std::domain_error("i not positive and above 0");
    
    int ctr = 0;
    
    while (i > 1) {
        if (i & 1) {
            i = i * 3 + 1;
        } else {
            i >>= 1;
        }
        ctr++;
    }
    
    return ctr;
}

}  // namespace collatz_conjecture