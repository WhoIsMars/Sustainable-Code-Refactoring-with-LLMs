#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t lines = take_down * 3 - 1;
    uint8_t bottles = start_bottles;

    for (uint16_t i = 0; i < lines; i += 3)
    {
        if (bottles == 2)
        {
            snprintf(song[i], 128, "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            snprintf(song[i + 1], 128, "Take one down and pass it around, %d bottle of beer on the wall.", bottles - 1);
        }
        else if (bottles == 1)
        {
            snprintf(song[i], 128, "%d bottle of beer on the wall, %d bottle of beer.", bottles, bottles);
            snprintf(song[i + 1], 128, "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else if (bottles == 0)
        {
            snprintf(song[i], 128, "No more bottles of beer on the wall, no more bottles of beer.");
            snprintf(song[i + 1], 128, "Go to the store and buy some more, 99 bottles of beer on the wall.");
        }
        else
        {
            snprintf(song[i], 128, "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            snprintf(song[i + 1], 128, "Take one down and pass it around, %d bottles of beer on the wall.", bottles - 1);
        }
        bottles--;
        if (i + 2 < lines) {
            song[i + 2] = "";
        }
    }
}