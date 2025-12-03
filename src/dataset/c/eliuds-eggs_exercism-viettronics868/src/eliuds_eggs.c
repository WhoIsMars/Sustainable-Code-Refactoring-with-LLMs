#include "eliuds_eggs.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

unsigned int count_One(const char *str_binary){
     unsigned int count = 0;
    size_t leng_str = strlen(str_binary);
    for (size_t i = 0; i < leng_str; i++){
        if (str_binary[i] == '1') count += 1;
    }
    return count;
}

size_t convert_decimal_binary(unsigned int number, char *str_binary){
    unsigned int cpy_number = number;
    size_t index_str = 0;
    while (cpy_number > 0){
        str_binary[index_str] = (cpy_number % 2) + '0';
        cpy_number = cpy_number / 2;
        index_str++;
    }
    str_binary[index_str+1] = '\0';
    return index_str;
}

unsigned int egg_count(unsigned int number){
    char string_binary[64] = {0};
    convert_decimal_binary(number, string_binary);
    return count_One(string_binary);
}
