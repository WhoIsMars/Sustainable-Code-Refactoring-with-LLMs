#include "beer_song.h"

#include <stdio.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    size_t line_count = 0;

    for (uint8_t i = 0; i < take_down; i++)
    {
        int start = start_bottles - i;
        int after = start - 1;

        if (start > 0)
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "%d %s of beer on the wall, %d %s of beer.",
                     start, (start == 1 ? "bottle" : "bottles"),
                     start, (start == 1 ? "bottle" : "bottles"));
        }
        else
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "No more bottles of beer on the wall, no more bottles of beer.");
        }

        if (after > 0)
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Take one down and pass it around, %d %s of beer on the wall.",
                     after, (after == 1 ? "bottle" : "bottles"));
        }
        else if (after == 0)
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }
    }
}