#include "beer_song.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
    size_t line_count = 0;
    int start = start_bottles;

    for (uint8_t i = 0; i < take_down; ++i, --start) {
        int after = start - 1;

        if (start > 0) {
            const char *unit_start = (start == 1) ? "bottle" : "bottles";
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "%d %s of beer on the wall, %d %s of beer.", start, unit_start, start,
                     unit_start);
        } else {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "No more bottles of beer on the wall, no more bottles of beer.");
        }

        if (after >= 0) {
            const char *unit_after = (after == 1) ? "bottle" : "bottles";
            const char *take_down_phrase = (after > 0) ? "Take one down and pass it around, "
                                                        : "Take it down and pass it around, ";

            if (after > 0) {
                snprintf(song[line_count++], MAX_LINE_LENGTH,
                         "%s%d %s of beer on the wall.", take_down_phrase, after, unit_after);
            } else {
                snprintf(song[line_count++], MAX_LINE_LENGTH,
                         "%sno more bottles of beer on the wall.", take_down_phrase);
            }

        } else {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }

        line_count++;
    }
}