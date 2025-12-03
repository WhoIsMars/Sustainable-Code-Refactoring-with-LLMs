#include "grains.h"


uint64_t square(uint8_t index)
{
    return pow(2, index - 1);
}


uint64_t total(void)
{
    uint64_t res = 0;

    for (int i = 1; i <= 64; i++) {
        res += square(i);
    }

    return res;
}
