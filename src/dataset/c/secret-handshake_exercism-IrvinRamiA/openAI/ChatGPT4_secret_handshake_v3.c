#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>

static char *convert_number_to_binary_5_bits(unsigned char number)
{
    char *binary_result = (char *)calloc(6, sizeof(char));
    for (int i = 4; i >= 0; i--)
    {
        binary_result[i] = (number & 1) ? '1' : '0';
        number >>= 1;
    }
    return binary_result;
}

const char **commands(size_t number)
{
    char *binary = convert_number_to_binary_5_bits((unsigned char)number);
    const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    unsigned char result_len = 0;

    for (unsigned char i = 0; i < 4; i++)
    {
        if (binary[i] == '1')
        {
            result_len++;
        }
    }

    char **result = (char **)malloc((result_len + 1) * sizeof(char *));
    unsigned char index = 0;

    for (unsigned char i = 0; i < 4; i++)
    {
        if (binary[i] == '1')
        {
            result[index++] = (char *)actions[i];
        }
    }

    if (binary[4] == '1' && result_len > 1)
    {
        for (unsigned char i = 0; i < result_len / 2; i++)
        {
            char *temp = result[i];
            result[i] = result[result_len - 1 - i];
            result[result_len - 1 - i] = temp;
        }
    }

    result[result_len] = NULL;
    free(binary);
    return (const char **)result;
}