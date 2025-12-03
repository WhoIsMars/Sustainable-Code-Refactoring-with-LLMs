/*
this is  a program convert a number from decimal to an array of binary numbers
Author LK
Date 2024-12-28
*/

#include "convert_2_result.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>


void decimal2binary(int decimal_number, int *array_binary){
    int cpy_number = decimal_number;
    size_t array_index = 0;
    if ((array_binary != NULL)){
        do {
            array_binary[array_index] = (cpy_number % 2);
            cpy_number = cpy_number / 2;
            array_index++;
        } while((cpy_number) != 0);
     
    } else {
        fprintf(stderr, "check 02 pointer-description %s ", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
}

void return_result(int *array_binary, user_result *p_user_record){
    if ((array_binary != NULL) && (p_user_record != NULL)){
        size_t max_current_list_allergens = 8;

        for (size_t i = 0; i < max_current_list_allergens; i++){
            if ((array_binary[i]) == 1){
                p_user_record->result = true;
               
            } else {
                strcpy(p_user_record->list_current_allergens[i], "");
              
            }
        }
        
    } else {
        fprintf(stderr, "check 03 pointers - NULL - description %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
