#include "beer_song.h"

#include <stdio.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    size_t line_count = 0;
    int current = start_bottles;
    
    for (uint8_t i = 0; i < take_down; i++, current--)
    {
        if (current > 0)
        {
            const char *unit = (current == 1) ? "bottle" : "bottles";
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "%d %s of beer on the wall, %d %s of beer.", current, unit, current, unit);
        }
        else
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "No more bottles of beer on the wall, no more bottles of beer.");
        }

        int after = current - 1;
        if (after > 0)
        {
            const char *unit = (after == 1) ? "bottle" : "bottles";
            snprintf(song[line_count++], MAX_LINE_LENGTH,
                     "Take one down and pass it around, %d %s of beer on the wall.", after, unit);
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

        song[line_count++] = "";
    }
}