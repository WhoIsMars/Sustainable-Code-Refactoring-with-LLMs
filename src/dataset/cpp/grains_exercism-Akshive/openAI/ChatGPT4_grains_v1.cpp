#include "grains.h"

namespace grains
{
    constexpr unsigned long long square(int sq) noexcept
    {
        return 1ULL << (sq - 1);
    }

    constexpr unsigned long long total() noexcept
    {
        return ~0ULL;
    }
}