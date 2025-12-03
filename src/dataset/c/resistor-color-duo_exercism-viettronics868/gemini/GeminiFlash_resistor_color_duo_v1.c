#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(const resistor_band_t *resis_band) {
    uint16_t value = 0;

    switch (resis_band[0]) {
        case BLACK:   value = 0; break;
        case BROWN:   value = 10; break;
        case RED:     value = 20; break;
        case ORANGE:  value = 30; break;
        case YELLOW:  value = 40; break;
        case GREEN:   value = 50; break;
        case BLUE:    value = 60; break;
        case VIOLET:  value = 70; break;
        case GREY:    value = 80; break;
        case WHITE:   value = 90; break;
        default:      value = 0; break; // Handle unexpected input
    }

    switch (resis_band[1]) {
        case BLACK:   value += 0; break;
        case BROWN:   value += 1; break;
        case RED:     value += 2; break;
        case ORANGE:  value += 3; break;
        case YELLOW:  value += 4; break;
        case GREEN:   value += 5; break;
        case BLUE:    value += 6; break;
        case VIOLET:  value += 7; break;
        case GREY:    value += 8; break;
        case WHITE:   value += 9; break;
        default:      break; // Handle unexpected input
    }

    return value;
}