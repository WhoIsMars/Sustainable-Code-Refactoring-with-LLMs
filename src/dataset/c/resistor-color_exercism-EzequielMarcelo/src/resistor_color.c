#include "resistor_color.h"
int color_code(resistor_band_t color)
{
    return color;
}
resistor_band_t *colors()
{
    static resistor_band_t list_colors[MAX_BANDS];

    for(int x = 0; x < MAX_BANDS; x++)
        list_colors[x] = (resistor_band_t) x;      

    return list_colors;
}