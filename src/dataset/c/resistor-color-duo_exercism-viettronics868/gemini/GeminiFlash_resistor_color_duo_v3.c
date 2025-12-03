#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(const resistor_band_t *resis_band) {
    uint16_t value_of_colors[2];
    const resistor_band_t color_list[] = {BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE,
                                            VIOLET, GREY, WHITE};
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (resis_band[i] == color_list[j]) {
                value_of_colors[i] = j;
                break;
            }
        }
    }

    return value_of_colors[0] * 10 + value_of_colors[1];
}