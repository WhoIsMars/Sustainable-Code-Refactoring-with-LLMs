#include "luhn.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

bool luhn(const char *num){
    if ((num != NULL) && (*num != '\0')){
        int sum = 0;
        size_t leng_num = strlen(num);
        if (leng_num == 1) return false;//single character is invalid
        char cpy_num[leng_num];
        strncpy(cpy_num, num, leng_num);

        //trim whitespaces from the array of characters
        int index = 0;
        for (size_t i = 0; i < leng_num; i++){
            if (!isspace(cpy_num[i])){ // check a space within the array of characters
                cpy_num[index] = cpy_num[i];
                index += 1;//index will show the total number of elements of the array
            }
        }

        //reassign the length of the array of characters
        if (index > 1) leng_num = index ;
        else return false;

        //check valid characters are numbers and whitespaces 
        for (size_t s = 0; s < leng_num; s++){
            if (!isdigit(cpy_num[s])) return false;
        }

        //convert a string to an array of integer
        int int_num[leng_num];
        for (size_t m = 0; m < leng_num; m++){
           int_num[m] = cpy_num[m] - '0';
        }
    
        //count second digits, starting from the right
        int count_second = leng_num -1;//point to right most digit
        while(count_second >= 0){
            if (count_second == 0){
                if (((leng_num - 1) % 2) == 0) break;//total elements of the array are odd then do not process element zero
            }
            int_num[count_second -1] *= 2;
            if (int_num[count_second - 1] > 9){
                int_num[count_second - 1] -= 9;
            }
            count_second -= 2;
        }

        //sum all elements of the array of integers
        for (size_t n = 0; n < leng_num; n++){
            sum += int_num[n];
        }

        //check sum for divisible by 10
        if ((sum % 10) == 0){
            return true;
        } else return false;

    } 
     else {
         return false;
     }
}

