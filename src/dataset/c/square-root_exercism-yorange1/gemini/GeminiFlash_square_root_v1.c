#include "square_root.h"

#include <stdint.h>

uint16_t square_root(uint16_t number)
{
    if (number == 0)
    {
        return 0;
    }

    uint32_t root = number;
    uint32_t next_root;

    while (true)
    {
        next_root = (root + (number / root)) >> 1;
        if (next_root >= root)
        {
            return (uint16_t)root;
        }
        root = next_root;
    }
}