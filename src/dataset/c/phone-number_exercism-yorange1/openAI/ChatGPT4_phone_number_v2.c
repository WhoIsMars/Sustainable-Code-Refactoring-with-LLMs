#include "phone_number.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MIN_PHONE_NUMBER_LEN (10)
#define MAX_PHONE_NUMBER_LEN (11)

char *phone_number_clean(const char *input)
{
    char temp[MAX_PHONE_NUMBER_LEN + 1] = {0};
    uint8_t count = 0;

    for (size_t i = 0; input[i] != '\0'; i++)
    {
        if (isdigit(input[i]))
        {
            if (count >= MAX_PHONE_NUMBER_LEN)
                return NULL;
            temp[count++] = input[i];
        }
    }

    if (count == MIN_PHONE_NUMBER_LEN && temp[0] >= '2' && temp[3] >= '2')
    {
        return strndup(temp, MIN_PHONE_NUMBER_LEN);
    }
    else if (count == MAX_PHONE_NUMBER_LEN && temp[0] == '1' && temp[1] >= '2' && temp[4] >= '2')
    {
        return strndup(&temp[1], MIN_PHONE_NUMBER_LEN);
    }

    return NULL;
}