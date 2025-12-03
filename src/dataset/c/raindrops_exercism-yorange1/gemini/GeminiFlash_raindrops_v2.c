#include "raindrops.h"

#include <stdio.h>
#include <stdbool.h>

char *convert(char result[], int drops) {
    result[0] = '\0'; // Initialize the string to empty

    bool has_factor = false;

    if (drops % 3 == 0) {
        strcat(result, "Pling");
        has_factor = true;
    }

    if (drops % 5 == 0) {
        strcat(result, "Plang");
        has_factor = true;
    }

    if (drops % 7 == 0) {
        strcat(result, "Plong");
        has_factor = true;
    }

    if (!has_factor) {
        sprintf(result, "%d", drops);
    }

    return result;
}