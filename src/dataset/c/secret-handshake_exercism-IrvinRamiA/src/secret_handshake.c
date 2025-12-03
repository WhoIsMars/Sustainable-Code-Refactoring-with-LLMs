#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *convert_number_to_binary_5_bits(unsigned char number)
{
    char *binary_result = (char *)malloc(5 * sizeof(char));
    unsigned char index = 0;
    unsigned char remainder = number % 2;
    unsigned char quotient = number /= 2;

    memset(binary_result, '0', 5);

    while (quotient != 0)
    {
        if (remainder == 1)
        {
            binary_result[index++] = '1';
        }
        else
        {
            binary_result[index++] = '0';
        }

        remainder = quotient % 2;
        quotient /= 2;
    }

    if (remainder == 1)
    {
        binary_result[index++] = '1';
    }

    binary_result[5] = '\0';

    return binary_result;
}

const char **commands(size_t number)
{
    char *binary = convert_number_to_binary_5_bits(number);
    unsigned char result_len = 0;
    unsigned char index = 0;

    /* Calculating number of output elements */
    for (unsigned char i = 0; i < strlen(binary) - 1; i++)
    {
        if (binary[i] == '1')
        {
            result_len++;
        }
    }

    /* Memory allocation */
    char **result = (char **)malloc(result_len * sizeof(char *));
    if (result_len == 0)
    {
        result[0] = NULL;
        return (const char **)result;
    }

    /* Basic commands */
    for (unsigned char i = 0; i < strlen(binary); i++)
    {
        if (i == 0 && binary[i] == '1')
        {
            result[index++] = "wink";
        }
        else if (i == 1 && binary[i] == '1')
        {
            result[index++] = "double blink";
        }
        else if (i == 2 && binary[i] == '1')
        {
            result[index++] = "close your eyes";
        }
        else if (i == 3 && binary[i] == '1')
        {
            result[index++] = "jump";
        }
    }

    /* Reversing action*/
    if (binary[4] == '1' && result_len >= 1)
    {
        for (unsigned char i = 0; i < result_len / 2; i++)
        {
            char *temp = result[i];
            result[i] = result[result_len - (1 + i)];
            result[result_len - (1 + i)] = temp;
        }
    }

    return (const char **)result;
}
