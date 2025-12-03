#include "raindrops.h"
#include <string.h>

void convert(char result[], int drop) {
    if (result == NULL) return;

    int isPling = (drop % 3 == 0);
    int isPlang = (drop % 5 == 0);
    int isPlong = (drop % 7 == 0);

    if (isPling || isPlang || isPlong) {
        char *ptr = result;
        if (isPling) {
            memcpy(ptr, "Pling", 5);
            ptr += 5;
        }
        if (isPlang) {
            memcpy(ptr, "Plang", 5);
            ptr += 5;
        }
        if (isPlong) {
            memcpy(ptr, "Plong", 5);
            ptr += 5;
        }
        *ptr = '\0';
    } else {
        convert_decimal_str(result, drop);
    }
}

void convert_decimal_str(char *str_of_decimal, int number) {
    if (str_of_decimal == NULL) return;

    char buffer[12];
    int len = 0;

    do {
        buffer[len++] = (number % 10) + '0';
        number /= 10;
    } while (number > 0);

    for (int i = 0; i < len; i++) {
        str_of_decimal[i] = buffer[len - 1 - i];
    }
    str_of_decimal[len] = '\0';
}