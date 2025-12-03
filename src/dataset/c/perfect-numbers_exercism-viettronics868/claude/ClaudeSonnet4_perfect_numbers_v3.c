#include "perfect_numbers.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

int classify_number(int number){
    if (number <= 0){
        return ERROR;
    }
    
    int sum = 1;
    int sqrt_num = (int)sqrt(number);
    
    for (int i = 2; i <= sqrt_num; i++){
        if (number % i == 0){
            sum += i;
            if (i != number / i){
                sum += number / i;
            }
        }
    }
    
    if (sum == number){
        return PERFECT_NUMBER;
    } else if (sum > number){
        return ABUNDANT_NUMBER;
    } else {
        return DEFICIENT_NUMBER;
    }
}