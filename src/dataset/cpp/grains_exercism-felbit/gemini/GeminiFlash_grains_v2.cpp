#include "grains.h"
#include <cmath>

namespace grains
{

    ull square(unsigned short _square)
    {
        return 1ULL << (_square - 1);
    }

    ull total()
    {
        return (1ULL << 64) - 1;
    }

}