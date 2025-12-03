#include "raindrops.h"
#include <stdio.h>
#include <string.h>

char *convert(char result[], int drops) {
    result[0] = '\0'; // Initialize the string to be empty

    int result_len = 0;

    if (drops % 3 == 0) {
        strcpy(result + result_len, "Pling");
        result_len += 5;
    }
    if (drops % 5 == 0) {
        strcpy(result + result_len, "Plang");
        result_len += 5;
    }
    if (drops % 7 == 0) {
        strcpy(result + result_len, "Plong");
        result_len += 5;
    }

    if (result_len == 0) {
        sprintf(result, "%d", drops);
    }

    return result;
}