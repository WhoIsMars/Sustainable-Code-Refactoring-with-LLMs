#include "resistor_color_duo.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


uint16_t color_code(const resistor_band_t *resis_band){
    resistor_band_t cpy_resis_band[5];
    memcpy(cpy_resis_band, resis_band, 5*sizeof(int));
    
    size_t leng_resis_band = sizeof(cpy_resis_band)/sizeof(cpy_resis_band[0]);
    const resistor_band_t color_list[] = {BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE,
                                            VIOLET, GREY, WHITE};
    size_t leng_color_list = sizeof(color_list)/sizeof(color_list[0]);
    uint16_t value_of_colors[leng_resis_band];
    for (uint16_t i = 0; i < (uint16_t)leng_resis_band; i++){
        for (uint16_t j = 0; j < (uint16_t)leng_color_list; j++){
            if (cpy_resis_band[i] == color_list[j]){
                value_of_colors[i] = j;
                break;
            }
        }  

    }
    uint16_t total_2_bands = value_of_colors[0]*pow(10, 1) + value_of_colors[1]*pow(10,0);
    return total_2_bands;
}