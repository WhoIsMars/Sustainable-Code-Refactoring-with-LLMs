#include "sum_of_multiples.h"
#include <numeric>
#include <unordered_set>

namespace sum_of_multiples
{
    int to(const std::set<int>& ns, int limit)
    {
        std::unordered_set<int> multiples;

        for (int n : ns)
        {
            if (n == 0) continue;
            for (int i = n; i < limit; i += n)
                multiples.insert(i);
        }

        return std::accumulate(multiples.begin(), multiples.end(), 0);
    }
}