#include "phone_number.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MIN_PHONE_NUMBER_LEN 10
#define MAX_PHONE_NUMBER_LEN 11

char *phone_number_clean(const char *input)
{
    char temp[MAX_PHONE_NUMBER_LEN + 1] = {0};
    size_t count = 0;

    for (const char *p = input; *p && count <= MAX_PHONE_NUMBER_LEN; p++)
    {
        if (isdigit(*p))
        {
            temp[count++] = *p;
        }
    }

    if ((count == MIN_PHONE_NUMBER_LEN && temp[0] >= '2' && temp[3] >= '2') ||
        (count == MAX_PHONE_NUMBER_LEN && temp[0] == '1' && temp[1] >= '2' && temp[4] >= '2'))
    {
        char *number = (char *)malloc(MIN_PHONE_NUMBER_LEN + 1);
        if (!number) return NULL;
        strncpy(number, count == MIN_PHONE_NUMBER_LEN ? temp : &temp[1], MIN_PHONE_NUMBER_LEN);
        number[MIN_PHONE_NUMBER_LEN] = '\0';
        return number;
    }

    return calloc(1, MIN_PHONE_NUMBER_LEN + 1);
}