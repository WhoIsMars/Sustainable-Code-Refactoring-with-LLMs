/*
this is a program that practice to use a struct with a member as an array.
Author LK
Date 2025-01-07
*/

#include "allergies.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


int int_to_binary(int score, int *array_binary){
    if (array_binary != NULL){
        if (score != 0){
            int cpy_score = score;
            size_t index_array = 0;
            while (cpy_score != 0){
                array_binary[index_array] = (cpy_score % 2);
                cpy_score /= 2;
                index_array++;
            }
        } else return 0;
    } else {
        fprintf(stderr, "error when convert integer to binary-description %s",strerror(errno));
        exit(EXIT_FAILURE);
    }

    return 1;
}

bool is_allergic_to(allergen_t allergy_test, int score){
    int array_of_binary[64] = {0}; //initialize an array of binary description of score
    size_t specific_allergen_count = 0;
    size_t allergen_count = 0;
    if (int_to_binary(score, array_of_binary) == 0){
        return false; 
    } else {
        for (size_t i = 0; i < ALLERGEN_COUNT; i++){
            if (array_of_binary[i] == 1){
                allergen_count++;        
                if (allergy_test == i){
                    specific_allergen_count++;
                } 
            } 
        }
        if (specific_allergen_count == 1){
            return true;
        } else return false;
    }

}

allergen_list_t get_allergens(int score){
    
    allergen_list_t allergens_list = {0, {false, false, false, false, false, false, false, false}};
    
    int array_of_binary[64] = {0}; //initialize an array of binary description of score
    
    size_t allergen_count = 0;
    if (int_to_binary(score, array_of_binary) != 0){
        
        for (size_t i = 0; i < ALLERGEN_COUNT; i++){
            if (array_of_binary[i] == 1){
                allergen_count++;        
            }
            allergens_list.allergens[i] = array_of_binary[i]; 
        }
        allergens_list.count = allergen_count;
        
    }

    return allergens_list;
 }
