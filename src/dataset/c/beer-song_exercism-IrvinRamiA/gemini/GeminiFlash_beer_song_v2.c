#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
    uint16_t line_index = 0;
    uint8_t bottles = start_bottles;
    char *line1 = NULL;
    char *line2 = NULL;

    for (uint8_t i = 0; i < take_down; ++i) {
        if (bottles == 0) {
            asprintf(&line1, "No more bottles of beer on the wall, no more bottles of beer.");
            asprintf(&line2, "Go to the store and buy some more, 99 bottles of beer on the wall.");
        } else if (bottles == 1) {
            asprintf(&line1, "%d bottle of beer on the wall, %d bottle of beer.", bottles, bottles);
            asprintf(&line2, "Take it down and pass it around, no more bottles of beer on the wall.");
        } else if (bottles == 2) {
            asprintf(&line1, "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            asprintf(&line2, "Take one down and pass it around, %d bottle of beer on the wall.", bottles - 1);
        } else {
            asprintf(&line1, "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            asprintf(&line2, "Take one down and pass it around, %d bottles of beer on the wall.", bottles - 1);
        }

        song[line_index++] = line1;
        song[line_index++] = line2;

        if (i < take_down - 1) {
            asprintf(&song[line_index++], "");
        }

        bottles--;
    }
}