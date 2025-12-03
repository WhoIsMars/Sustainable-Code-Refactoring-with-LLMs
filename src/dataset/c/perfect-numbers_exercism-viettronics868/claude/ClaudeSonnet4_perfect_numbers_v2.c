#include "perfect_numbers.h"
#include <stdint.h>
#include <stdio.h>

int classify_number(int number){
    if (number <= 0){
        return ERROR;
    }
    
    int sum = 1; // 1 is always a divisor for numbers > 1
    int sqrt_num = 1;
    
    // Find square root efficiently
    while (sqrt_num * sqrt_num <= number) {
        sqrt_num++;
    }
    sqrt_num--;
    
    // Find divisors up to square root
    for (int i = 2; i <= sqrt_num; i++){
        if ((number % i) == 0){
            sum += i;
            // Add the corresponding divisor if it's different
            if (i != number / i) {
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