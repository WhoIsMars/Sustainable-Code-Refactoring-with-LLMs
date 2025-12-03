#include "square_root.h"

#include <math.h>

uint16_t square_root(uint16_t number)
{
    if (number == 0)
    {
        return 0;
    }

    double x0 = number, xi;
    do
    {
        xi = 0.5 * (x0 + number / x0);
        if (fabs(x0 - xi) < 1e-7)
        {
            break;
        }
        x0 = xi;
    } while (1);

    return (uint16_t)xi;
}