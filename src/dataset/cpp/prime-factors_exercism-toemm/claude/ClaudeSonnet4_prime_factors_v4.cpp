#include "prime_factors.h"

#include <vector>

namespace prime_factors {

using namespace std;

vector<long long> of(long long i) {
    vector<long long> out;
    out.reserve(32);
    
    while (i % 2 == 0) {
        out.push_back(2);
        i /= 2;
    }
    
    for (long long divisor = 3; divisor * divisor <= i; divisor += 2) {
        while (i % divisor == 0) {
            out.push_back(divisor);
            i /= divisor;
        }
    }
    
    if (i > 2) {
        out.push_back(i);
    }
    
    return out;
}

}  // namespace prime_factors