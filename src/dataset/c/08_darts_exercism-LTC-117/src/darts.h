#ifndef DARTS_H
#define DARTS_H


#include <stdint.h>


typedef struct {
    float x_axis;
    float y_axis;
} coordinate_t;


uint8_t score(coordinate_t coordinates);

#endif
