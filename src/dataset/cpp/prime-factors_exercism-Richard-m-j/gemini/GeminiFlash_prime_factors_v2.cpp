#include "prime_factors.h"
#include <cmath>

namespace prime_factors {

    vector<int> of(int n) {
        vector<int> result;
        while (n > 1) {
            for (int i = 2; i <= sqrt(n); ++i) {
                if (n % i == 0) {
                    result.push_back(i);
                    n /= i;
                    goto next_iteration;
                }
            }
            result.push_back(n);
            break;

            next_iteration:;
        }
        return result;
    }
}  // namespace prime_factors