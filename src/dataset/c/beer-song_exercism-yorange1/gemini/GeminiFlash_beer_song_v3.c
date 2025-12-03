#include "beer_song.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH (1024)

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    size_t line_count = 0;

    const char *bottle = "bottle";
    const char *bottles = "bottles";
    const char *take_one = "Take one down and pass it around, ";
    const char *take_it = "Take it down and pass it around, ";
    const char *go_to_store = "Go to the store and buy some more, 99 bottles of beer on the wall.";
    const char *no_more_bottles = "No more bottles of beer";
    const char *on_the_wall = " on the wall.";
    const char *of_beer = " of beer";
    const char *comma_space = ", ";

    int start = start_bottles;
    int after = start_bottles - 1;

    for (uint8_t i = 0; i < take_down; i++, start--, after--)
    {
        if (start > 0)
        {
            const char *unit = (start == 1) ? bottle : bottles;
            snprintf(song[line_count], MAX_LINE_LENGTH, "%d %s%s%s%d %s%s", start, unit, of_beer, comma_space, start, unit, of_beer);
        }
        else
        {
            snprintf(song[line_count], MAX_LINE_LENGTH, "%s%s%s%s", no_more_bottles, of_beer, on_the_wall, comma_space);
            strncat(song[line_count], no_more_bottles, MAX_LINE_LENGTH - strlen(song[line_count]) - 1);
            strncat(song[line_count], of_beer, MAX_LINE_LENGTH - strlen(song[line_count]) - 1);
        }
        line_count++;

        if (after > 0)
        {
            const char *unit = (after == 1) ? bottle : bottles;
            snprintf(song[line_count], MAX_LINE_LENGTH, "%s%d %s%s", take_one, after, unit, on_the_wall);
        }
        else if (after == 0)
        {
            snprintf(song[line_count], MAX_LINE_LENGTH, "%s%s", take_it, no_more_bottles);
            strncat(song[line_count], of_beer, MAX_LINE_LENGTH - strlen(song[line_count]) - 1);
            strncat(song[line_count], on_the_wall, MAX_LINE_LENGTH - strlen(song[line_count]) - 1);
        }
        else
        {
            strncpy(song[line_count], go_to_store, MAX_LINE_LENGTH - 1);
            song[line_count][MAX_LINE_LENGTH - 1] = '\0';
            break;
        }

        line_count++;
        line_count++;
    }
}