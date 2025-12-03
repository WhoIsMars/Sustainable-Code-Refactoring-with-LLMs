#include "phone_number.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MIN_PHONE_NUMBER_LEN (10)
#define MAX_PHONE_NUMBER_LEN (11)

char *phone_number_clean(const char *input)
{
    char *number = (char *)calloc(MIN_PHONE_NUMBER_LEN + 1, sizeof(char));
    if (!number)
        return NULL;

    size_t count = 0;
    for (size_t i = 0; input[i] != '\0' && count <= MAX_PHONE_NUMBER_LEN; i++)
    {
        if (isdigit((unsigned char)input[i]))
        {
            if (count < MAX_PHONE_NUMBER_LEN)
                number[count++] = input[i];
        }
    }

    if (count == MIN_PHONE_NUMBER_LEN && number[0] >= '2' && number[3] >= '2')
    {
        return number;
    }
    else if (count == MAX_PHONE_NUMBER_LEN && number[0] == '1' && number[1] >= '2' && number[4] >= '2')
    {
        memmove(number, number + 1, MIN_PHONE_NUMBER_LEN);
        number[MIN_PHONE_NUMBER_LEN] = '\0';
        return number;
    }

    free(number);
    return NULL;
}