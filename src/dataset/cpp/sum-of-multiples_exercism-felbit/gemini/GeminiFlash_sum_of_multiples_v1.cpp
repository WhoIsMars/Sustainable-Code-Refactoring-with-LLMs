#include "sum_of_multiples.h"
#include <numeric>

namespace sum_of_multiples
{
    int to(std::set<int> ns, int limit)
    {
        std::set<int> multiples;
        std::vector<int> unique_multiples;

        for (int n : ns) {
            if (n == 0) continue; 

            for (int i = n; i < limit; i += n) {
                if (multiples.insert(i).second) {
                    unique_multiples.push_back(i);
                }
            }
        }

        return std::accumulate(unique_multiples.begin(), unique_multiples.end(), 0);
    }
}