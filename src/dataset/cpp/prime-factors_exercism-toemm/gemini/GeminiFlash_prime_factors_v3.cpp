#include "prime_factors.h"

#include <vector>
#include <cmath>

namespace prime_factors {

using namespace std;


vector<long long> of(long long i) {

    vector<long long> out;

    if (i <= 1) {
        return out;
    }

    while (i % 2 == 0) {
        out.push_back(2);
        i /= 2;
    }

    for (long long divisor = 3; divisor <= sqrt(i); divisor += 2) {
        while (i % divisor == 0) {
            out.push_back(divisor);
            i /= divisor;
        }
    }

    if (i > 1) {
        out.push_back(i);
    }

    return out;

}


}  // namespace prime_factors