#include "raindrops.h"

#include <stdio.h>
#include <stdbool.h>

char *convert(char result[], int drops) {
    result[0] = '\0';
    bool has_factor = false;
    size_t len = 0;

    if (drops % 3 == 0) {
        strcpy(result, "Pling");
        len = 5;
        has_factor = true;
    }

    if (drops % 5 == 0) {
        strcpy(result + len, "Plang");
        len += 5;
        has_factor = true;
    }

    if (drops % 7 == 0) {
        strcpy(result + len, "Plong");
        len += 5;
        has_factor = true;
    }

    if (!has_factor) {
        sprintf(result, "%d", drops);
    }

    return result;
}