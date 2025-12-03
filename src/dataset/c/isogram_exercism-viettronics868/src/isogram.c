#include "isogram.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

bool is_isogram(const char phrase[]){
    
    if (phrase != NULL){
        size_t leng_phrase = strlen(phrase);
        if (leng_phrase <= 1){
            return 1;
        }
        for (size_t i = 0; i < leng_phrase - 1; i++){
            if ((phrase[i] != '-') && (phrase[i] != ' ')){       
                for (size_t j = i+1; j < leng_phrase; j++){
                    if((phrase[i] == phrase[j]) || 
                    (phrase[i] == phrase[j] + 32) || 
                    (phrase[i] == phrase[j] - 32)){
                    return 0;
                    }
                }
            }
        }
        return 1;
    } else return 0;

}
