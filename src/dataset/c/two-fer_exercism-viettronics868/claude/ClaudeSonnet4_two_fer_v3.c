#include "two_fer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void two_fer(char *buffer, const char *name){
    if (name != NULL) {
        strcpy(buffer, "One for ");
        strcat(buffer, name);
        strcat(buffer, ", one for me.");
    } else {
        strcpy(buffer, "One for you, one for me.");
    }
}