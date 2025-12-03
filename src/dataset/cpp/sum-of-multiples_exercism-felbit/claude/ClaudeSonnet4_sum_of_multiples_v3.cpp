#include "sum_of_multiples.h"

namespace sum_of_multiples
{
    int to(std::set<int> ns, int limit)
    {
        if (limit <= 1 || ns.empty()) return 0;
        
        std::set<int> multiples;
        multiples.reserve(limit / 2);
        
        for (int n : ns) {
            if (n <= 0 || n >= limit) continue;
            for (int multiple = n; multiple < limit; multiple += n) {
                multiples.insert(multiple);
            }
        }
        
        int sum = 0;
        for (int m : multiples) {
            sum += m;
        }
        return sum;
    }
}