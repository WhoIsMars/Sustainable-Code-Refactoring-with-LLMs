#include "prime_factors.h"

#include <vector>

namespace prime_factors {

using namespace std;


vector<long long> of(long long i) {

    vector<long long> out;

    int divisor{2};

    while(i != 1) {
        if (i % divisor == 0) {
            i /= divisor;
            out.push_back(divisor);
        } else {
            divisor++;
        }

    }

    return out;

}


}  // namespace prime_factors
