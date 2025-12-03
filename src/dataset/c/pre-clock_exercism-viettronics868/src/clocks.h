#ifndef CLOCKS_H
#define CLOCKS_H
#include <stdbool.h>


#define MAX_STR_LENG sizeof("#####:#####")*sizeof(char)

struct clock_t {
    char text[MAX_STR_LENG];
};



struct clock_t create_clocks(double hour, double minute);


struct clock_t add_minute(struct clock_t clock, double minute);

bool clock_is_equal(struct clock_t a, struct clock_t b);


#endif