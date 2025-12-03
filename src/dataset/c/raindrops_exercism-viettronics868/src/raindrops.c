#include "raindrops.h"
#include <string.h>

void convert(char result[], int drop){
    char pling[] = "Pling";
    size_t leng_pli = strlen(pling);
    char plang[] = "Plang";
    size_t leng_pla = strlen(plang);
    char plong[] = "Plong";
    
    if (result != NULL){
        if (((drop % 3) == 0) && ((drop % 5) == 0) && ((drop % 7) == 0)){
            strcpy(result, pling);
            strcpy(result+leng_pli, plang);
            strcpy(result+leng_pli+leng_pla, plong);
        } else if (((drop % 3) == 0) && ((drop % 5) == 0)){
            strcpy(result, pling);
            strcpy(result+leng_pli, plang);
        } else if (((drop % 5) == 0) && ((drop % 7) == 0)){
            strcpy(result, plang);
            strcpy(result+leng_pla, plong);
        } else if (((drop % 3) == 0) && ((drop % 7) == 0)){
            strcpy(result, pling);
            strcpy(result+leng_pli, plong);
        } else if ((drop % 3) == 0){
            strcpy(result, pling);            
        } else if ((drop % 5) == 0){
            strcpy(result, plang);
        } else if ((drop % 7) == 0){
            strcpy(result, plong);
        } else {
            convert_decimal_str(result, drop);
            
        }
        
    }
}

void convert_decimal_str(char *str_of_decimal, int number){
    size_t index_str = 0;
    int cpy_number = number;
    char rev_str_decimal[64] = {0};
    if (str_of_decimal != NULL){
        
        while (( cpy_number ) > 0){
            rev_str_decimal[index_str] = (cpy_number % 10) + '0';
            index_str++;
            cpy_number = cpy_number /10;            
        }
        for (size_t i =0; i < index_str; i++){
            str_of_decimal[index_str-1 -i] = rev_str_decimal[i];
        }
        str_of_decimal[index_str] = '\0';
        
    }
}
