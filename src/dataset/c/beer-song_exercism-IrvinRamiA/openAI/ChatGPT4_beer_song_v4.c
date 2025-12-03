#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t line = 0;

    for (uint8_t i = 0; i < take_down; i++)
    {
        if (start_bottles > 2)
        {
            line += sprintf(song[line], "%d bottles of beer on the wall, %d bottles of beer.", start_bottles, start_bottles);
            line += sprintf(song[line], "Take one down and pass it around, %d bottles of beer on the wall.", --start_bottles);
        }
        else if (start_bottles == 2)
        {
            line += sprintf(song[line], "%d bottles of beer on the wall, %d bottles of beer.", start_bottles, start_bottles);
            line += sprintf(song[line], "Take one down and pass it around, %d bottle of beer on the wall.", --start_bottles);
        }
        else if (start_bottles == 1)
        {
            line += sprintf(song[line], "%d bottle of beer on the wall, %d bottle of beer.", start_bottles, start_bottles);
            line += sprintf(song[line], "Take it down and pass it around, no more bottles of beer on the wall.");
            start_bottles--;
        }
        else
        {
            line += sprintf(song[line], "No more bottles of beer on the wall, no more bottles of beer.");
            line += sprintf(song[line], "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }
    }
}