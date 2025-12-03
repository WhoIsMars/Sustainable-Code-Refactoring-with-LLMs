#include "beer_song.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
    size_t line_count = 0;
    int start = start_bottles;

    for (uint8_t i = 0; i < take_down; ++i) {
        if (start > 0) {
            const char *unit = (start == 1) ? "bottle" : "bottles";
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "%d %s of beer on the wall, %d %s of beer.", start, unit, start, unit);

            int after = start - 1;
            if (after > 0) {
                unit = (after == 1) ? "bottle" : "bottles";
                snprintf(song[line_count++], MAX_LINE_LENGTH,
                         "Take one down and pass it around, %d %s of beer on the wall.", after, unit);
            } else if (after == 0) {
                snprintf(song[line_count++], MAX_LINE_LENGTH,
                         "Take it down and pass it around, no more bottles of beer on the wall.");
            }
        } else {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "No more bottles of beer on the wall, no more bottles of beer.");
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }

        start--;
        line_count++;
    }
}