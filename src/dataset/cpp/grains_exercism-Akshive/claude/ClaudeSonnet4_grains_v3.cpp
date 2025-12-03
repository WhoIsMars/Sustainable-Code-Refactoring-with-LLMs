#include "grains.h"
#include <cstdint>

namespace grains
{
    unsigned long long square(int sq)
    {
        return 1ULL << (sq - 1);
    }
    
    unsigned long long total()
    {
        return UINT64_MAX;
    }
}