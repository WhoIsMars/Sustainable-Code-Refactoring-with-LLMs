#include "perfect_numbers.h"
#include <stdint.h>
#include <stdio.h>

int classify_number(int number){
    if (number <= 0){
        return ERROR;
    }
    
    int sum = 1; // 1 is always a divisor for numbers > 1
    
    if (number == 1) {
        sum = 0; // 1 has no proper divisors
    } else {
        // Only check up to sqrt(number) and add both divisors at once
        for (int i = 2; i * i <= number; i++){
            if ((number % i) == 0){
                sum += i;
                // Add the corresponding divisor if it's different from i
                if (i != number / i) {
                    sum += number / i;
                }
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