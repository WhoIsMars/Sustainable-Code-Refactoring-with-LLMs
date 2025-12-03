#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "beer_song.h"

static const char* const TEMPLATES[] = {
    "No more bottles of beer on the wall, no more bottles of beer.",
    "Go to the store and buy some more, 99 bottles of beer on the wall.",
    "%d bottle of beer on the wall, %d bottle of beer.",
    "Take it down and pass it around, no more bottles of beer on the wall.",
    "%d bottles of beer on the wall, %d bottles of beer.",
    "Take one down and pass it around, %d bottle of beer on the wall.",
    "Take one down and pass it around, %d bottles of beer on the wall."
};

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    uint16_t line_idx = 0;
    uint8_t current_bottles = start_bottles;
    
    for (uint8_t verse = 0; verse < take_down; verse++)
    {
        if (current_bottles == 0)
        {
            strcpy(song[line_idx++], TEMPLATES[0]);
            strcpy(song[line_idx++], TEMPLATES[1]);
        }
        else if (current_bottles == 1)
        {
            sprintf(song[line_idx++], TEMPLATES[2], current_bottles, current_bottles);
            strcpy(song[line_idx++], TEMPLATES[3]);
        }
        else if (current_bottles == 2)
        {
            sprintf(song[line_idx++], TEMPLATES[4], current_bottles, current_bottles);
            sprintf(song[line_idx++], TEMPLATES[5], current_bottles - 1);
        }
        else
        {
            sprintf(song[line_idx++], TEMPLATES[4], current_bottles, current_bottles);
            sprintf(song[line_idx++], TEMPLATES[6], current_bottles - 1);
        }
        
        if (verse < take_down - 1)
        {
            song[line_idx++][0] = '\0';
        }
        
        current_bottles = (current_bottles == 0) ? 99 : current_bottles - 1;
    }
}