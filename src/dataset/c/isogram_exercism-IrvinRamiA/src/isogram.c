#include "isogram.h"
#include <string.h>
#include <stdint.h>
#include <ctype.h>

/*

[0][1][2][3][4][5][6]
[i][s][o][g][r][a][m]

Iterar i desde 0 hasta (length - 1):
    Iterarar j desde i + 1 hasta (length - 1):
        Si phrase[i] == phrase[j]:
            return false
return true

*/

/*

Used functions from libraries:

Prototype: int tolower(int argument);
Library: ctype.h

+++++

Prototype: int isalpha(int argument);
Library: ctype.h

+++++

Prototype: char *strchr(const char *str, int c);
Library: string.h
Example:

#include <stdio.h>
#include <string.h>

int main () {
   const char str[] = "http://www.tutorialspoint.com";
   const char ch = '.';
   char *ret;

   ret = strchr(str, ch);

   printf("String after |%c| is - |%s|\n", ch, ret);
   
   return(0);
}

Result: String after |.| is - |.tutorialspoint.com|

*/

bool is_isogram(const char phrase[])
{
    if (phrase == NULL)
    {
        return false;
    }

    uint8_t length = strlen(phrase);

    for (uint8_t i = 0; i < length - 1; i++)                                    // Iteration from index [0] to index [lenght - 1] 
    {
        for (uint8_t j = i + 1; j < length; j++)                                // Iteration from index [i + 1] to index [lenght]
        {
            if (tolower(phrase[i]) == tolower(phrase[j]) &&
            isalpha(phrase[i]) && isalpha(phrase[j]))                           // If a letter is repeated -> return false 
            {
                return false;
            }
        }
    }

    return true;
}
