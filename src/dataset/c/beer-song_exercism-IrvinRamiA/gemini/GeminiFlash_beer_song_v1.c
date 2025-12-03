#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
    uint16_t line_index = 0;
    uint8_t bottles = start_bottles;
    char buffer[128]; 

    for (uint8_t i = 0; i < take_down; ++i) {
        if (bottles == 2) {
            sprintf(buffer, "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            song[line_index++] = strdup(buffer);
            sprintf(buffer, "Take one down and pass it around, %d bottle of beer on the wall.", bottles - 1);
            song[line_index++] = strdup(buffer);
        } else if (bottles == 1) {
            sprintf(buffer, "%d bottle of beer on the wall, %d bottle of beer.", bottles, bottles);
            song[line_index++] = strdup(buffer);
            sprintf(buffer, "Take it down and pass it around, no more bottles of beer on the wall.");
            song[line_index++] = strdup(buffer);
        } else if (bottles == 0) {
            sprintf(buffer, "No more bottles of beer on the wall, no more bottles of beer.");
            song[line_index++] = strdup(buffer);
            sprintf(buffer, "Go to the store and buy some more, 99 bottles of beer on the wall.");
            song[line_index++] = strdup(buffer);
        } else {
            sprintf(buffer, "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            song[line_index++] = strdup(buffer);
            sprintf(buffer, "Take one down and pass it around, %d bottles of beer on the wall.", bottles - 1);
            song[line_index++] = strdup(buffer);
        }

        if (i < take_down - 1) {
            song[line_index++] = strdup(""); 
        }
        bottles--;
    }
}