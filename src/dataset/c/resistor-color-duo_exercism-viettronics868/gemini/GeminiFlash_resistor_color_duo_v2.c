#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(const resistor_band_t *resis_band) {
    uint16_t value_of_colors[2];
    
    // Directly map resistor bands to their color code values.
    // This avoids unnecessary loops and memory copies.
    switch (resis_band[0]) {
        case BLACK:   value_of_colors[0] = 0; break;
        case BROWN:   value_of_colors[0] = 1; break;
        case RED:     value_of_colors[0] = 2; break;
        case ORANGE:  value_of_colors[0] = 3; break;
        case YELLOW:  value_of_colors[0] = 4; break;
        case GREEN:   value_of_colors[0] = 5; break;
        case BLUE:    value_of_colors[0] = 6; break;
        case VIOLET:  value_of_colors[0] = 7; break;
        case GREY:    value_of_colors[0] = 8; break;
        case WHITE:   value_of_colors[0] = 9; break;
        default:      value_of_colors[0] = 0; // Handle unexpected values gracefully
    }

    switch (resis_band[1]) {
        case BLACK:   value_of_colors[1] = 0; break;
        case BROWN:   value_of_colors[1] = 1; break;
        case RED:     value_of_colors[1] = 2; break;
        case ORANGE:  value_of_colors[1] = 3; break;
        case YELLOW:  value_of_colors[1] = 4; break;
        case GREEN:   value_of_colors[1] = 5; break;
        case BLUE:    value_of_colors[1] = 6; break;
        case VIOLET:  value_of_colors[1] = 7; break;
        case GREY:    value_of_colors[1] = 8; break;
        case WHITE:   value_of_colors[1] = 9; break;
        default:      value_of_colors[1] = 0; // Handle unexpected values gracefully
    }

    return value_of_colors[0] * 10 + value_of_colors[1];
}