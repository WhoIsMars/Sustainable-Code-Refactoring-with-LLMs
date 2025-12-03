#include <stdlib.h>
#include <stdio.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    for (uint8_t i = 0; i < take_down; i++)
    {
        if (start_bottles > 2)
        {
            sprintf(song[i * 2], "%d bottles of beer on the wall, %d bottles of beer.", start_bottles, start_bottles);
            sprintf(song[i * 2 + 1], "Take one down and pass it around, %d bottles of beer on the wall.", start_bottles - 1);
        }
        else if (start_bottles == 2)
        {
            sprintf(song[i * 2], "%d bottles of beer on the wall, %d bottles of beer.", start_bottles, start_bottles);
            sprintf(song[i * 2 + 1], "Take one down and pass it around, %d bottle of beer on the wall.", start_bottles - 1);
        }
        else if (start_bottles == 1)
        {
            sprintf(song[i * 2], "%d bottle of beer on the wall, %d bottle of beer.", start_bottles, start_bottles);
            sprintf(song[i * 2 + 1], "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else
        {
            sprintf(song[i * 2], "No more bottles of beer on the wall, no more bottles of beer.");
            sprintf(song[i * 2 + 1], "Go to the store and buy some more, 99 bottles of beer on the wall.");
            break;
        }
        start_bottles--;
    }
}