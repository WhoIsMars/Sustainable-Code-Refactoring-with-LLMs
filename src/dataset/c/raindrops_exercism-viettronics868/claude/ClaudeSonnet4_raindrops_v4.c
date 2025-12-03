#include "raindrops.h"
#include <string.h>

void convert(char result[], int drop){
    if (result == NULL) return;
    
    char *ptr = result;
    int div3 = (drop % 3) == 0;
    int div5 = (drop % 5) == 0;
    int div7 = (drop % 7) == 0;
    
    if (div3) {
        memcpy(ptr, "Pling", 5);
        ptr += 5;
    }
    if (div5) {
        memcpy(ptr, "Plang", 5);
        ptr += 5;
    }
    if (div7) {
        memcpy(ptr, "Plong", 5);
        ptr += 5;
    }
    
    if (!(div3 || div5 || div7)) {
        convert_decimal_str(result, drop);
    } else {
        *ptr = '\0';
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
    
    while (temp > 0) {
        temp /= 10;
        ptr++;
    }
    
    *ptr = '\0';
    
    while (number > 0) {
        *(--ptr) = (number % 10) + '0';
        number /= 10;
    }
}