#include "gigasecond.h"
#include <time.h>

#define GIGASEC 1000000000

void gigasecond(time_t input, char *output, size_t size){
    time_t result = input + GIGASEC;
    struct tm *my_time = gmtime(&result);
    strftime(output, size, "%Y-%m-%d %H:%M:%S", my_time);
}