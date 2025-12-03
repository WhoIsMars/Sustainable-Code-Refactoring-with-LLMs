#include <stdint.h>
#include <errno.h>


#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H

typedef enum{
    BLACK,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE,
}resistor_band_t;

typedef struct 
{
    uint16_t value;
    char *unit;
}resistor_value_t;


resistor_value_t color_code(const resistor_band_t *color_band);


#endif
