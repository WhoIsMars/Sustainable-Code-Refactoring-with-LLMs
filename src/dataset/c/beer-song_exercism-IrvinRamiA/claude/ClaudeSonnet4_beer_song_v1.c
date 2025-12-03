#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t line_idx = 0;
    uint8_t bottles = start_bottles;
    
    for (uint8_t verse = 0; verse < take_down; verse++)
    {
        if (bottles == 2)
        {
            sprintf(song[line_idx++], "2 bottles of beer on the wall, 2 bottles of beer.");
            sprintf(song[line_idx++], "Take one down and pass it around, 1 bottle of beer on the wall.");
        }
        else if (bottles == 1)
        {
            sprintf(song[line_idx++], "1 bottle of beer on the wall, 1 bottle of beer.");
            sprintf(song[line_idx++], "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else if (bottles == 0)
        {
            strcpy(song[line_idx++], "No more bottles of beer on the wall, no more bottles of beer.");
            strcpy(song[line_idx++], "Go to the store and buy some more, 99 bottles of beer on the wall.");
        }
        else
        {
            sprintf(song[line_idx++], "%d bottles of beer on the wall, %d bottles of beer.", bottles, bottles);
            sprintf(song[line_idx++], "Take one down and pass it around, %d bottles of beer on the wall.", bottles - 1);
        }
        
        if (verse < take_down - 1)
        {
            song[line_idx++][0] = '\0';
        }
        
        bottles--;
    }
}