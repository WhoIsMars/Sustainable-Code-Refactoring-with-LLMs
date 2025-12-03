/*
this is a program that reads a long input and returns the input by a pointer
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "process_long_input.h"


//pass double pointer because I  will try to reallocate the memory and update the new
//address
int parse_input(int fd, size_t chunk_size, char **complete_message){
    char buffer[chunk_size];
    int data_read = 0;
    size_t memory_len = 0;
    while ((data_read = read(fd, buffer, chunk_size)) > 0){
        //reallocate memory
        char *buffer_alloc = realloc(*complete_message, memory_len + data_read + 1);
        //check and verify the memory reallocation
        if (buffer_alloc == NULL){
            perror("error from reallocation the memory");

            return EXIT_FAILURE;
        }
        //dereferencing double pointer to update the memory allocation
        *complete_message = buffer_alloc;

        //append the new word of data to the existing string and 
        //overwrite the previous null terminator
        memcpy(*complete_message + memory_len, buffer, data_read);
        
        //update the memory length
        memory_len += data_read;

        //add () to the dereferrencing double pointer to get higher precedence 
        //and add the null terminator
        (*complete_message)[memory_len] = '\0';


    }
    //check and verify the data read. *Note: important step!!!
    if (data_read == -1){
        perror("error reading from stdin");
        free(*complete_message);//prevent memory leak
        *complete_message = NULL;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}