#include "prime_factors.h"

#include <vector>

namespace prime_factors {

using namespace std;

vector<long long> of(long long i) {
    vector<long long> out;
    
    // Handle factor 2 separately to avoid even number checks
    while (i % 2 == 0) {
        out.push_back(2);
        i /= 2;
    }
    
    // Check odd divisors starting from 3
    for (long long divisor = 3; divisor * divisor <= i; divisor += 2) {
        while (i % divisor == 0) {
            out.push_back(divisor);
            i /= divisor;
        }
    }
    
    // If i is still greater than 1, it's a prime factor
    if (i > 1) {
        out.push_back(i);
    }
    
    return out;
}

}  // namespace prime_factors