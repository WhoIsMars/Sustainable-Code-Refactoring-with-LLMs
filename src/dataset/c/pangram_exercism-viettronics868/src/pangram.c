#include "pangram.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

bool is_pangram(const char *sentence){

    char alphabet_list[] = "abcdefghijklmnopwrstuvwxyz";
    size_t alpha_list_leng = (size_t)strlen(alphabet_list);
    
    size_t count_letter = 0;
    if (sentence != NULL){
        size_t sen_leng = (size_t)strlen(sentence);
        for (size_t i = 0; i < alpha_list_leng; i++){
           
            
            size_t index_sentence = 0;
            size_t cpy_count_letter = count_letter;
            while (index_sentence < sen_leng){
                
                
                if ((alphabet_list[i] == sentence[index_sentence]) || ((alphabet_list[i] - 32) == sentence[index_sentence])){
                    count_letter += 1;
                    

                    break;
                }
                index_sentence++;
            }
            if (cpy_count_letter == count_letter){
                return 0;
            }
        }        
    }
    if (count_letter == alpha_list_leng){
        return 1;
    } else return 0;
}
