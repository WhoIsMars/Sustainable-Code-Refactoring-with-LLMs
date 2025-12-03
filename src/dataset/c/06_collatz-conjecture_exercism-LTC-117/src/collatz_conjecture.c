#include "collatz_conjecture.h"
#include <stdio.h>


int steps(int start)
{
    if (start <= 0) return ERROR_VALUE;

    int counter = 0;

    while (start) {
        if (start == 1) {
            goto out;
        }

        if (start % 2 == 0) {
            start /= 2;
        } else {
            start = (3 * start) + 1;
        }

        counter++;
    }

out:
    return counter;
}
