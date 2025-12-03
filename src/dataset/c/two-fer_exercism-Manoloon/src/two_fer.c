#include "two_fer.h"
#include <string.h>
#include <stdio.h>

/*
| Name   | Dialogue                    |
| :----- | :-------------------------- |
| Alice  | One for Alice, one for me.  |
| Bohdan | One for Bohdan, one for me. |
|        | One for you, one for me.    |
| Zaphod | One for Zaphod, one for me. |
*/
void two_fer(char *buffer, const char *name) 
{
    if (name == 0)
    {
        strcpy(buffer,"One for you, one for me.");
        return;
    }
    int count = 0;
    while (count < 2)
    {
        if(count == 0)
        {
            sprintf(buffer,"One for %s, ", name);
        }
        else
        {
            strcat(buffer,"one for me.");
        }
        count++;
    }  
}
