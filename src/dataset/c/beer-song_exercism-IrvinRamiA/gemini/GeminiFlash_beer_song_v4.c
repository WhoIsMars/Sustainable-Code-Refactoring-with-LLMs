#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t line_index = 0;
    uint8_t bottles = start_bottles;

    for (uint8_t verse = 0; verse < take_down; ++verse)
    {
        if (bottles == 2)
        {
            sprintf(song[line_index++], "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            sprintf(song[line_index++], "Take one down and pass it around, %d bottle of beer on the wall.", bottles - 1);
        }
        else if (bottles == 1)
        {
            sprintf(song[line_index++], "%d bottle of beer on the wall, %d bottle of beer.", bottles, bottles);
            sprintf(song[line_index++], "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else if (bottles == 0)
        {
            sprintf(song[line_index++], "No more bottles of beer on the wall, no more bottles of beer.");
            sprintf(song[line_index++], "Go to the store and buy some more, 99 bottles of beer on the wall.");
        }
        else
        {
            sprintf(song[line_index++], "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            sprintf(song[line_index++], "Take one down and pass it around, %d bottles of beer on the wall.", bottles - 1);
        }

        if (verse < take_down - 1) {
            sprintf(song[line_index++], "");
        }
        bottles--;
    }
}