#include "beer_song.h"
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
    size_t line_count = 0;
    int start = start_bottles;
    int after;

    for (uint8_t i = 0; i < take_down; ++i) {
        after = start - 1;

        // First verse line
        if (start > 0) {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "%d %s of beer on the wall, %d %s of beer.",
                     start, (start == 1 ? "bottle" : "bottles"),
                     start, (start == 1 ? "bottle" : "bottles"));
        } else {
            strcpy(song[line_count++], "No more bottles of beer on the wall, no more bottles of beer.");
        }

        // Second verse line
        if (after > 0) {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Take one down and pass it around, %d %s of beer on the wall.",
                     after, (after == 1 ? "bottle" : "bottles"));
        } else if (after == 0) {
            strcpy(song[line_count++], "Take it down and pass it around, no more bottles of beer on the wall.");
        } else {
            strcpy(song[line_count++], "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break; // Last verse
        }

        line_count++;
        start--;
    }
}