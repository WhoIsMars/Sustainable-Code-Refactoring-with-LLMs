#include "beer_song.h"

#include <stdio.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    const char *bottle_singular = "bottle";
    const char *bottle_plural = "bottles";

    for (uint8_t i = 0; i < take_down; i++)
    {
        uint8_t current = start_bottles - i;
        uint8_t next = current > 0 ? current - 1 : 99;

        const char *current_unit = current == 1 ? bottle_singular : bottle_plural;
        const char *next_unit = next == 1 ? bottle_singular : bottle_plural;

        if (current > 0)
        {
            snprintf(song[2 * i], MAX_LINE_LENGTH,
                     "%d %s of beer on the wall, %d %s of beer.", current, current_unit, current, current_unit);
            snprintf(song[2 * i + 1], MAX_LINE_LENGTH,
                     "Take one down and pass it around, %s %s of beer on the wall.",
                     next > 0 ? next : "no more", next > 0 ? next_unit : bottle_plural);
        }
        else
        {
            snprintf(song[2 * i], MAX_LINE_LENGTH,
                     "No more bottles of beer on the wall, no more bottles of beer.");
            snprintf(song[2 * i + 1], MAX_LINE_LENGTH,
                     "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }
    }
}