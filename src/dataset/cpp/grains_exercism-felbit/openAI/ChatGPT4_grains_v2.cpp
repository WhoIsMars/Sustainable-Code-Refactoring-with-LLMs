#include "grains.h"

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