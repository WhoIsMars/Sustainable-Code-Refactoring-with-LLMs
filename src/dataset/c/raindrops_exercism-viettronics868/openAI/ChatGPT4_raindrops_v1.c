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

    bool is_divisible_by_3 = (drop % 3 == 0);
    bool is_divisible_by_5 = (drop % 5 == 0);
    bool is_divisible_by_7 = (drop % 7 == 0);

    if (is_divisible_by_3 || is_divisible_by_5 || is_divisible_by_7) {
        result[0] = '\0'; // Initialize result as an empty string
        if (is_divisible_by_3) strcat(result, "Pling");
        if (is_divisible_by_5) strcat(result, "Plang");
        if (is_divisible_by_7) strcat(result, "Plong");
    } else {
        convert_decimal_str(result, drop);
    }
}