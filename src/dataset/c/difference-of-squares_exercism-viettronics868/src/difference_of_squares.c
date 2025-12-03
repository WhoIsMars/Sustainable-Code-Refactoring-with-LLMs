#include "difference_of_squares.h"
#include <stdio.h>
#include <math.h>

unsigned int square_of_sum(unsigned int number){
    unsigned int i;
    unsigned int total = 0;
    for(i =1; i <= number; i++ ){
        total += i;
    }
    return(pow(total, 2));
}

unsigned int sum_of_squares(unsigned int number){
    unsigned int i;
    unsigned int total = 0;
    for(i = 1; i <= number; i++){
        total += pow(i, 2);
    }
    return total;
}

unsigned int difference_of_squares(unsigned int number){
    return(square_of_sum(number) - sum_of_squares(number));
}