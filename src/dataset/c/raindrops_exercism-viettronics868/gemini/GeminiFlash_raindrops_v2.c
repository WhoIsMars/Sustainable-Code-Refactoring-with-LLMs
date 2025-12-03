#include "raindrops.h"
#include <stdio.h>

void convert(char result[], int drop) {
    if (result == NULL) return;

    result[0] = '\0'; // Initialize result to an empty string

    if (drop % 3 == 0) {
        strcat(result, "Pling");
    }
    if (drop % 5 == 0) {
        strcat(result, "Plang");
    }
    if (drop % 7 == 0) {
        strcat(result, "Plong");
    }

    if (result[0] == '\0') {
        sprintf(result, "%d", drop);
    }
}