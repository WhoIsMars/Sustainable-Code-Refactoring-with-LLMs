#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    unsigned char result = 1;

    while (result * result < number)
    {
        result++;
    }
    
    return result;
}
