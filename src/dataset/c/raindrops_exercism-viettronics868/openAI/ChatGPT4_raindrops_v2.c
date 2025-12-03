#include "raindrops.h"
#include <string.h>
#include <stdbool.h>

void convert(char result[], int drop) {
    if (result == NULL) return;

    bool divisible_by_3 = (drop % 3 == 0);
    bool divisible_by_5 = (drop % 5 == 0);
    bool divisible_by_7 = (drop % 7 == 0);

    size_t pos = 0;

    if (divisible_by_3) {
        strcpy(result + pos, "Pling");
        pos += 5;
    }
    if (divisible_by_5) {
        strcpy(result + pos, "Plang");
        pos += 5;
    }
    if (divisible_by_7) {
        strcpy(result + pos, "Plong");
        pos += 5;
    }

    if (pos == 0) {
        convert_decimal_str(result, drop);
    } else {
        result[pos] = '\0';
    }
}

void convert_decimal_str(char *str_of_decimal, int number) {
    if (str_of_decimal == NULL) return;

    sprintf(str_of_decimal, "%d", number);
}