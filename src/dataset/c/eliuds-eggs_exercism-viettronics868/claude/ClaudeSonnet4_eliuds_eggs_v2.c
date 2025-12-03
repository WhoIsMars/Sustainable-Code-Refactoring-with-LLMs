#include "eliuds_eggs.h"
#include <stdint.h>

unsigned int egg_count(unsigned int number){
    unsigned int count = 0;
    while (number) {
        count += number & 1;
        number >>= 1;
    }
    return count;
}