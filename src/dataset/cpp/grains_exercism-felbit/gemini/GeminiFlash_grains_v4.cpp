#include "grains.h"
#include <cmath>

namespace grains
{

    ull square(unsigned short _square)
    {
        if (_square == 0 || _square > 64) {
            throw std::domain_error("Square must be between 1 and 64");
        }
        return 1ULL << (_square - 1);
    }

    ull total()
    {
        return (1ULL << 64) - 1;
    }

}