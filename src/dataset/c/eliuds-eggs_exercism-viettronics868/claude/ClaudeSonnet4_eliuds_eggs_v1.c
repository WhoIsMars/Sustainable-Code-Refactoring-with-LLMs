#include "eliuds_eggs.h"
#include <stdint.h>

unsigned int count_One(const char *str_binary){
    unsigned int count = 0;
    const char *ptr = str_binary;
    while (*ptr) {
        if (*ptr == '1') count++;
        ptr++;
    }
    return count;
}

size_t convert_decimal_binary(unsigned int number, char *str_binary){
    if (number == 0) {
        str_binary[0] = '0';
        str_binary[1] = '\0';
        return 1;
    }
    
    size_t index_str = 0;
    while (number > 0){
        str_binary[index_str] = (number & 1) + '0';
        number >>= 1;
        index_str++;
    }
    str_binary[index_str] = '\0';
    return index_str;
}

unsigned int egg_count(unsigned int number){
    unsigned int count = 0;
    while (number) {
        count += number & 1;
        number >>= 1;
    }
    return count;
}