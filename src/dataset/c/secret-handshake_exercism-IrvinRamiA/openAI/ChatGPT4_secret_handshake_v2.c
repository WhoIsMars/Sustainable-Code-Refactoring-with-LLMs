#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>

static void convert_number_to_binary_5_bits(unsigned char number, char *binary_result)
{
    for (int i = 4; i >= 0; i--)
    {
        binary_result[i] = (number & 1) ? '1' : '0';
        number >>= 1;
    }
    binary_result[5] = '\0';
}

const char **commands(size_t number)
{
    char binary[6];
    convert_number_to_binary_5_bits(number, binary);

    const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    const char **result = (const char **)malloc(4 * sizeof(char *));
    unsigned char index = 0;

    for (unsigned char i = 0; i < 4; i++)
    {
        if (binary[i] == '1')
        {
            result[index++] = actions[i];
        }
    }

    if (binary[4] == '1' && index > 1)
    {
        for (unsigned char i = 0; i < index / 2; i++)
        {
            const char *temp = result[i];
            result[i] = result[index - 1 - i];
            result[index - 1 - i] = temp;
        }
    }

    result = (const char **)realloc(result, index * sizeof(char *));
    return result;
}