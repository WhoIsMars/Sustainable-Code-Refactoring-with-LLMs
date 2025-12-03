#include "two_fer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void two_fer(char *buffer, const char *name){
    char general_msg[] = "One for you, one for me.";    
    char one_for[] = "One for ";
    char one_for_me[] = ", one for me.";
    size_t leng_one_for = strlen(one_for);
    size_t leng_one_for_me = strlen(one_for_me);
    size_t leng_total = 0;
    if (name != NULL){
        size_t leng_name = strlen(name);//check NULL before using to avoid core dummped
        for (size_t i = 0; i < leng_one_for; i++){
            buffer[i] = one_for[i];
        }
        leng_total += leng_one_for;
        for (size_t j = 0; j < leng_name; j++){
            buffer[j+leng_total] = name[j];
        }
           leng_total += leng_name;
        for (size_t k = 0; k <= leng_one_for_me; k++){
            buffer[k+leng_total] = one_for_me[k];
        }
    } else {
        for (size_t i = 0; i <= strlen(general_msg); i++){
            buffer[i] = general_msg[i];    
        }
    }
}



