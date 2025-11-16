#include "collatz_conjecture.h"
#include <stdexcept>

unsigned int collatz_conjecture::steps(const int &_num) {
    if (_num <= 0) 
        throw std::domain_error("not a positive integer");
    
    unsigned int steps = 0;
    unsigned int num = static_cast<unsigned int>(_num);
    
    while (num > 1) {
        num = (num & 1) ? (num * 3 + 1) : (num >> 1);
        ++steps;
    }
    return steps;
}