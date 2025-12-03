#include "sum_of_multiples.h"
#include <numeric>

namespace sum_of_multiples
{
    int to(std::set<int> ns, int limit)
    {
        int sum = 0;
        std::vector<bool> is_multiple(limit, false);

        for (int n : ns)
        {
            if (n == 0) continue;
            for (int i = n; i < limit; i += n)
                is_multiple[i] = true;
        }

        for (int i = 0; i < limit; ++i)
        {
            if (is_multiple[i]) sum += i;
        }

        return sum;
    }
}