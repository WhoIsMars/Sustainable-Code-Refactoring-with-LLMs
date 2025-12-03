#include "raindrops.h"
#include <string.h>
#include <stdbool.h>

void convert_decimal_str(char *str_of_decimal, int number) {
    if (str_of_decimal != NULL) {
        sprintf(str_of_decimal, "%d", number);
    }
}

void convert(char result[], int drop) {
    if (result == NULL) return;

    bool isDivisibleBy3 = (drop % 3 == 0);
    bool isDivisibleBy5 = (drop % 5 == 0);
    bool isDivisibleBy7 = (drop % 7 == 0);

    if (isDivisibleBy3 || isDivisibleBy5 || isDivisibleBy7) {
        result[0] = '\0';
        if (isDivisibleBy3) strcat(result, "Pling");
        if (isDivisibleBy5) strcat(result, "Plang");
        if (isDivisibleBy7) strcat(result, "Plong");
    } else {
        convert_decimal_str(result, drop);
    }
}