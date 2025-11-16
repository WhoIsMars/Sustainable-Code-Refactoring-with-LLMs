#include "nth_prime.h"

#include <math.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int nth_prime::nth(int number) {
    if (number == 0) {
        throw domain_error("Weird case.");
    }
    if (number == 1) {
        return 2;
    }
    
    int upper_bound = 10 + (int)(number * (log(number) + log(log(number))));
    vector<bool> is_prime(upper_bound + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    int count = 0;
    
    for (int i = 2; i <= upper_bound; ++i) {
        if (is_prime[i]) {
            ++count;
            if (count == number) {
                return i;
            }
            
            if (i <= upper_bound / i) {
                for (int j = i * i; j <= upper_bound; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
    
    return 2;
}