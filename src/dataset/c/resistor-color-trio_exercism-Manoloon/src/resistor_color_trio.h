#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H
#include <stdint.h>

typedef enum 
{
    BLACK = 0,
    BROWN = 1,
    RED = 2,
    ORANGE = 3,
    YELLOW = 4,
    GREEN = 5,
    BLUE = 6,
    VIOLET = 7,
    GREY = 8,
    WHITE = 9,
}resistor_band_t;
typedef enum
{
    OHMS = 1,
    KILOOHMS = 1000,
    MEGAOHMS = 1000000,
    GIGAOHMS = 1000000000,
}resistor_unit_t;
typedef struct
{
    resistor_unit_t unit;
    uint16_t value;
}resistor_value_t;
resistor_value_t color_code(const resistor_band_t colors[1]);
#endif
