#include "perfect_numbers.h"
#include <stdint.h>
#include <stdio.h>

int classify_number(int number){
    int cpy_number = number;
    int perfect_arr[100] = {0};
    int index_arr = 0;
    int sum = 0;
    if (number <= 0){
 
        return ERROR;
    }
    for (int i = 1; i < cpy_number; i++){
        if ((cpy_number % i) == 0){
            perfect_arr[index_arr] = i;
            index_arr++;
        }
    }
    for (int j = 0; j < index_arr; j++){
        sum += perfect_arr[j];
    }
    if (sum == number){
        return PERFECT_NUMBER;
    } else if (sum > number){
        return ABUNDANT_NUMBER;
    } else return DEFICIENT_NUMBER;
}

