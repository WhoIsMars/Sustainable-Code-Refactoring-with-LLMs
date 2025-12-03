#include "raindrops.h"
#include <string.h>

void convert(char result[], int drop){
    if (result == NULL) return;
    
    char *ptr = result;
    int has_sound = 0;
    
    if (drop % 3 == 0) {
        memcpy(ptr, "Pling", 5);
        ptr += 5;
        has_sound = 1;
    }
    if (drop % 5 == 0) {
        memcpy(ptr, "Plang", 5);
        ptr += 5;
        has_sound = 1;
    }
    if (drop % 7 == 0) {
        memcpy(ptr, "Plong", 5);
        ptr += 5;
        has_sound = 1;
    }
    
    if (has_sound) {
        *ptr = '\0';
    } else {
        convert_decimal_str(result, drop);
    }
}

void convert_decimal_str(char *str_of_decimal, int number){
    if (str_of_decimal == NULL) return;
    
    if (number == 0) {
        str_of_decimal[0] = '0';
        str_of_decimal[1] = '\0';
        return;
    }
    
    char *ptr = str_of_decimal;
    int temp = number;
    int digits = 0;
    
    while (temp > 0) {
        temp /= 10;
        digits++;
    }
    
    ptr[digits] = '\0';
    
    while (number > 0) {
        ptr[--digits] = (number % 10) + '0';
        number /= 10;
    }
}