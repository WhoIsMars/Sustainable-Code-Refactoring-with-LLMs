#include "resistor_color.h"

// Static array of resistor bands.  Marked const to reside in read-only memory.
static const resistor_band_t resistor_bands[] = {BLACK, BROWN, RED, ORANGE, YELLOW,
                                          GREEN, BLUE, VIOLET, GREY, WHITE};

resistor_band_t color_code(resistor_band_t code)
{
    return code; // Directly return the input as it's already the correct enum value.
}

const resistor_band_t *colors(void)
{
    return resistor_bands; // Return a const pointer to prevent modification.
}