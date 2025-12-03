#include "eliuds_eggs.h"
#include <stdint.h>

unsigned int count_One(const char *str_binary) {
    unsigned int count = 0;
    while (*str_binary) {
        if (*str_binary == '1') {
            count++;
        }
        str_binary++;
    }
    return count;
}

size_t convert_decimal_binary(unsigned int number, char *str_binary) {
    size_t index_str = 0;
    if (number == 0) {
        str_binary[0] = '0';
        str_binary[1] = '\0';
        return 1;
    }

    while (number > 0) {
        str_binary[index_str++] = (number & 1) + '0';
        number >>= 1;
    }
    str_binary[index_str] = '\0';

    // Reverse the string
    for (size_t i = 0, j = index_str - 1; i < j; i++, j--) {
        char temp = str_binary[i];
        str_binary[i] = str_binary[j];
        str_binary[j] = temp;
    }

    return index_str;
}

unsigned int egg_count(unsigned int number) {
    unsigned int count = 0;
    while (number > 0) {
        count += (number & 1);
        number >>= 1;
    }
    return count;
}