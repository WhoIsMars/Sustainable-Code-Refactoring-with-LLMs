#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t line_index = 0;

    for (uint8_t i = 0; i < take_down; i++)
    {
        if (start_bottles > 2)
        {
            line_index += sprintf(song[line_index], "%d bottles of beer on the wall, %d bottles of beer.", start_bottles, start_bottles);
            line_index += sprintf(song[line_index], "Take one down and pass it around, %d bottles of beer on the wall.", start_bottles - 1);
        }
        else if (start_bottles == 2)
        {
            line_index += sprintf(song[line_index], "%d bottles of beer on the wall, %d bottles of beer.", start_bottles, start_bottles);
            line_index += sprintf(song[line_index], "Take one down and pass it around, %d bottle of beer on the wall.", start_bottles - 1);
        }
        else if (start_bottles == 1)
        {
            line_index += sprintf(song[line_index], "%d bottle of beer on the wall, %d bottle of beer.", start_bottles, start_bottles);
            line_index += sprintf(song[line_index], "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else
        {
            line_index += sprintf(song[line_index], "No more bottles of beer on the wall, no more bottles of beer.");
            line_index += sprintf(song[line_index], "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }
        start_bottles--;
        if (i < take_down - 1)
        {
            line_index += sprintf(song[line_index], "");
        }
    }
}