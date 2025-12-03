#include "gigasecond.h"
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define gigasec 1000000000
void gigasecond(time_t input, char *output, size_t size){
    time_t cpy_input = input + gigasec;
  
    struct tm *my_time = gmtime(&cpy_input);
    strftime(output, size, "%Y-%m-%d %H:%M:%S", my_time);
   

}
