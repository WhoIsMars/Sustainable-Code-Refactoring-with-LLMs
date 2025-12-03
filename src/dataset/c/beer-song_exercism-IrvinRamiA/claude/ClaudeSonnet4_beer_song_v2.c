#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t song_index = 0;
    uint8_t current_bottles = start_bottles;
    
    for (uint8_t verse = 0; verse < take_down; verse++)
    {
        if (current_bottles == 2)
        {
            sprintf(song[song_index++], "2 bottles of beer on the wall, 2 bottles of beer.");
            sprintf(song[song_index++], "Take one down and pass it around, 1 bottle of beer on the wall.");
        }
        else if (current_bottles == 1)
        {
            sprintf(song[song_index++], "1 bottle of beer on the wall, 1 bottle of beer.");
            sprintf(song[song_index++], "Take it down and pass it around, no more bottles of beer on the wall.");
        }
        else if (current_bottles == 0)
        {
            sprintf(song[song_index++], "No more bottles of beer on the wall, no more bottles of beer.");
            sprintf(song[song_index++], "Go to the store and buy some more, 99 bottles of beer on the wall.");
        }
        else
        {
            sprintf(song[song_index++], "%d bottles of beer on the wall, %d bottles of beer.", current_bottles, current_bottles);
            sprintf(song[song_index++], "Take one down and pass it around, %d bottles of beer on the wall.", current_bottles - 1);
        }
        
        if (verse < take_down - 1)
        {
            song[song_index++][0] = '\0';
        }
        
        current_bottles--;
    }
}