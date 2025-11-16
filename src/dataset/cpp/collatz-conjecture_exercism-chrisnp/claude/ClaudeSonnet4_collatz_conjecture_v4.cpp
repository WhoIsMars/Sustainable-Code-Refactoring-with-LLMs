#include "collatz_conjecture.h"
#include <stdexcept>

unsigned int collatz_conjecture::steps (const int &_num) {
    if (_num <= 0) 
        throw std::domain_error("not a positive integer");
    
    unsigned int num = static_cast<unsigned int>(_num);
    unsigned int steps = 0;
    
    while (num > 1) {
        if (num & 1) {
            num = num + (num << 1) + 1;
        } else {
            num >>= 1;
        }
        ++steps;
    }
    return steps;
}