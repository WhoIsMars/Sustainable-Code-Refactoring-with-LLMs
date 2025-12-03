#ifndef DARTS_H
#define DARTS_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct 
{
    float x;
    float y;
} coordinate_t;

uint8_t score(coordinate_t coordinate);

#endif
