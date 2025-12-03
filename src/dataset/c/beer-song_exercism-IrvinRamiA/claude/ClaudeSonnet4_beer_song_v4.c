#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "beer_song.h"

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    static const char* const templates[] = {
        "No more bottles of beer on the wall, no more bottles of beer.",
        "Go to the store and buy some more, 99 bottles of beer on the wall.",
        "%d bottle of beer on the wall, %d bottle of beer.",
        "Take it down and pass it around, no more bottles of beer on the wall.",
        "%d bottles of beer on the wall, %d bottles of beer.",
        "Take one down and pass it around, %d bottle of beer on the wall.",
        "Take one down and pass it around, %d bottles of beer on the wall."
    };
    
    uint16_t song_idx = 0;
    uint8_t bottles = start_bottles;
    
    for (uint8_t verse = 0; verse < take_down; verse++) {
        if (bottles == 0) {
            strcpy(song[song_idx++], templates[0]);
            strcpy(song[song_idx++], templates[1]);
        } else if (bottles == 1) {
            sprintf(song[song_idx++], templates[2], bottles, bottles);
            strcpy(song[song_idx++], templates[3]);
        } else if (bottles == 2) {
            sprintf(song[song_idx++], templates[4], bottles, bottles);
            sprintf(song[song_idx++], templates[5], bottles - 1);
        } else {
            sprintf(song[song_idx++], templates[4], bottles, bottles);
            sprintf(song[song_idx++], templates[6], bottles - 1);
        }
        
        if (verse < take_down - 1) {
            song[song_idx++][0] = '\0';
        }
        
        bottles = (bottles == 0) ? 99 : bottles - 1;
    }
}