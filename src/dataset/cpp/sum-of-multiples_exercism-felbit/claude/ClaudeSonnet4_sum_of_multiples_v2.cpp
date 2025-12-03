#include "sum_of_multiples.h"

namespace sum_of_multiples
{
    int to(std::set<int> ns, int limit)
    {
        std::set<int> multiples;
        multiples.reserve(limit / 2);  // Reserve approximate capacity
        
        for (int n : ns) {
            if (n <= 0 || n >= limit) continue;  // Skip invalid multiples
            for (int multiple = n; multiple < limit; multiple += n) {
                multiples.insert(multiple);
            }
        }

        int sum = 0;
        for (int m : multiples) sum += m;
        return sum;
    }
}