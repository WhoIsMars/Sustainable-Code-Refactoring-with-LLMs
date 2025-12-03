#include "sum_of_multiples.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit){
    
    unsigned int sum = 0;

    if ((factors != NULL)  && (limit != 0)){
    
        //create an array of length of multiples
        unsigned int leng_of_multiples[number_of_factors];
        
        //declare double pointer to store the factor array
        unsigned int **p_factor;
        //allocate memory for double pointer
        p_factor = malloc(sizeof(unsigned int *) * number_of_factors);//allocate memory for row
        if (p_factor == NULL){
            fprintf(stderr, "cannot allocated memory for row-description %s \n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < number_of_factors; i++){//allocate memory for column
            
            p_factor[i] = malloc(sizeof(unsigned int) * limit);
            if (p_factor[i] == NULL){
                fprintf(stderr, "cannot not allocate memory for column-description %s \n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            //check if the factor is not zero. If it is zero, then the length of the multiples is zero
            if (factors[i] != 0){
                //create an array of multiples of the factors
                unsigned int multiples = factors[i];
                unsigned int index = 0;
                while (multiples < limit){
                    p_factor[i][index] = multiples;
                    index++;
                    multiples += factors[i];
                }
                leng_of_multiples[i] = index;//store index as the length of the multiples    
            }
        
            

        }

        //create an array of unique multiples
        unsigned int *unique_multiples;
        unique_multiples = malloc(sizeof(unsigned int) * limit);
        if (unique_multiples == NULL){
            fprintf(stderr, "cannot allocate memory for unique array -description %s \n", strerror(errno));
            exit(EXIT_FAILURE);
        }


      
        unsigned int index = 0;
        for (unsigned int k = 0; k < limit; k++){
            int break_flag = 0;
            for (size_t m = 0; m < number_of_factors; m++){
                //check if the factor is not zero. if it is zero, then the multiples is zero
                if (factors[m] != 0){
                    for (size_t n = 0; n < leng_of_multiples[m]; n++){
                        if (p_factor[m][n] == k){
                            unique_multiples[index] = k;
                            index++;
                            break_flag = 1;
                            break; // exit the for (n) loop
                        }
                    }
                }
                
                if (break_flag == 1){
                    break; // exit the for (m) loop
                }
            }
        }

        //sum of the unique multiples
        
        for (size_t i = 0; i < index; i++){
            sum += unique_multiples[i];
        }


        //deallocation of memory
        free(unique_multiples);
        unique_multiples = NULL;

        for (size_t i =0; i < number_of_factors; i++){
            free(p_factor[i]);
            p_factor[i] = NULL;
        }
        free(p_factor);
        p_factor = NULL;

        
    }
   

    return sum;
}

