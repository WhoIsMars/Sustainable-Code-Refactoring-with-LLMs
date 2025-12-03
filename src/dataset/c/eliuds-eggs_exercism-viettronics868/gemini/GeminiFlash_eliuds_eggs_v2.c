#include "eliuds_eggs.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

unsigned int count_One(const char *str_binary){
    unsigned int count = 0;
    size_t leng_str = strlen(str_binary);
    for (size_t i = 0; i < leng_str; i++){
        if (str_binary[i] == '1') {
            count++;
        }
    }
    return count;
}

size_t convert_decimal_binary(unsigned int number, char *str_binary){
    size_t index_str = 0;
    if (number == 0) {
        str_binary[0] = '0';
        str_binary[1] = '\0';
        return 1;
    }

    while (number > 0){
        str_binary[index_str++] = (number & 1) + '0';
        number >>= 1;
    }
    str_binary[index_str] = '\0';
    return index_str;
}

unsigned int egg_count(unsigned int number){
    char string_binary[64] = {0};
    size_t len = convert_decimal_binary(number, string_binary);

    // Reverse the string in place, since convert_decimal_binary produces a reversed string
    for (size_t i = 0; i < len / 2; i++) {
        char temp = string_binary[i];
        string_binary[i] = string_binary[len - 1 - i];
        string_binary[len - 1 - i] = temp;
    }

    return count_One(string_binary);
}