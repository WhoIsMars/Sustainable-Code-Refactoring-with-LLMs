#include "eliuds_eggs.h"
#include <stdint.h>

unsigned int count_One(const char *str_binary){
    unsigned int count = 0;
    while (*str_binary) {
        count += (*str_binary++ == '1');
    }
    return count;
}

size_t convert_decimal_binary(unsigned int number, char *str_binary){
    size_t index_str = 0;
    do {
        str_binary[index_str++] = (number & 1) + '0';
        number >>= 1;
    } while (number > 0);
    str_binary[index_str] = '\0';
    return index_str;
}

unsigned int egg_count(unsigned int number){
    unsigned int count = 0;
    while (number > 0) {
        count += (number & 1);
        number >>= 1;
    }
    return count;
}