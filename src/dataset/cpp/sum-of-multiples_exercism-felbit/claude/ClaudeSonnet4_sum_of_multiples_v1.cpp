#include "sum_of_multiples.h"

namespace sum_of_multiples
{
    int to(std::set<int> ns, int limit)
    {
        if (limit <= 1) return 0;
        
        // Remove zeros and negatives, and numbers >= limit
        std::vector<int> valid_ns;
        valid_ns.reserve(ns.size());
        for (int n : ns) {
            if (n > 0 && n < limit) {
                valid_ns.push_back(n);
            }
        }
        
        if (valid_ns.empty()) return 0;
        
        std::set<int> multiples;
        multiples.reserve(limit / 2); // Reasonable estimate
        
        for (int n : valid_ns) {
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