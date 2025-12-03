#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>

static const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};

static char *convert_number_to_binary_5_bits(unsigned char number)
{
    char *binary_result = (char *)malloc(6 * sizeof(char));
    for (int i = 4; i >= 0; i--)
    {
        binary_result[4 - i] = (number & (1 << i)) ? '1' : '0';
    }
    binary_result[5] = '\0';
    return binary_result;
}

const char **commands(size_t number)
{
    char *binary = convert_number_to_binary_5_bits((unsigned char)number);
    unsigned char result_len = 0;

    for (int i = 0; i < 4; i++)
    {
        if (binary[i] == '1')
        {
            result_len++;
        }
    }

    const char **result = (const char **)malloc((result_len + 1) * sizeof(char *));
    unsigned char index = 0;

    if (result_len > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (binary[i] == '1')
            {
                result[index++] = actions[i];
            }
        }

        if (binary[4] == '1')
        {
            for (unsigned char i = 0; i < result_len / 2; i++)
            {
                const char *temp = result[i];
                result[i] = result[result_len - 1 - i];
                result[result_len - 1 - i] = temp;
            }
        }
    }

    result[result_len] = NULL;
    free(binary);
    return result;
}