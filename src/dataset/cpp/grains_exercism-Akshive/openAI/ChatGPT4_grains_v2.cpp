#include "grains.h"

namespace grains
{
    constexpr unsigned long long square(int sq)
    {
        return 1ULL << (sq - 1);
    }

    constexpr unsigned long long total()
    {
        return ~0ULL;
    }
}