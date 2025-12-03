#ifndef CLOCKS_H
#define CLOCKS_H
#include <stdbool.h>
#include "time_v.h"


#define MAX_STR_LENG sizeof("####:####")*sizeof(char)

typedef struct{
    char text[MAX_STR_LENG];
}clock_t;



clock_t create_clocks(double hour, double minute);


clock_t add_minute(clock_t clock, double minute);

bool clock_is_equal(clock_t a, clock_t b);


#endif