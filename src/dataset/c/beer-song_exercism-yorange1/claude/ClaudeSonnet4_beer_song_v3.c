#include "beer_song.h"

#include <stdio.h>

#define MAX_LINE_LENGTH (1024)

static const char bottle[] = "bottle";
static const char bottles[] = "bottles";

static const char first_line_format[] = "%d %s of beer on the wall, %d %s of beer.";
static const char no_more_first_line[] = "No more bottles of beer on the wall, no more bottles of beer.";
static const char take_one_format[] = "Take one down and pass it around, %d %s of beer on the wall.";
static const char take_it_format[] = "Take it down and pass it around, no more bottles of beer on the wall.";
static const char go_store_line[] = "Go to the store and buy some more, 99 bottles of beer on the wall.";

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    size_t line_count = 0;
    int current = start_bottles;

    for (uint8_t i = 0; i < take_down; i++, current--)
    {
        const int after = current - 1;
        
        if (current > 0)
        {
            const char *unit = (current == 1) ? bottle : bottles;
            snprintf(song[line_count++], MAX_LINE_LENGTH, first_line_format, current, unit, current, unit);
        }
        else
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH, "%s", no_more_first_line);
        }

        if (after > 0)
        {
            const char *unit = (after == 1) ? bottle : bottles;
            snprintf(song[line_count++], MAX_LINE_LENGTH, take_one_format, after, unit);
        }
        else if (after == 0)
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH, "%s", take_it_format);
        }
        else
        {
            snprintf(song[line_count++], MAX_LINE_LENGTH, "%s", go_store_line);
            break;
        }

        song[line_count++][0] = '\0';
    }
}