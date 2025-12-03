#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H

typedef enum
{
    BLACK,
    BROWN,
    RED,
    ORANGE,
    YELLOW, 
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE
} resistor_band_t;

typedef enum
{
    OHMS,
    KILOOHMS
} unit_t;

typedef struct
{
    unsigned int value;
    unit_t unit;
} resistor_value_t;

resistor_value_t color_code(resistor_band_t resistor_band[]);

#endif
