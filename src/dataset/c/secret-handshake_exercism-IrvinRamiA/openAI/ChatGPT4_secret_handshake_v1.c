#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>

static char *convert_number_to_binary_5_bits(unsigned char number)
{
    char *binary_result = (char *)malloc(6 * sizeof(char)); // Allocate 6 for null terminator
    for (int i = 4; i >= 0; i--)
    {
        binary_result[4 - i] = (number & (1 << i)) ? '1' : '0';
    }
    binary_result[5] = '\0';
    return binary_result;
}

const char **commands(size_t number)
{
    static const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    char *binary = convert_number_to_binary_5_bits(number);
    unsigned char result_len = 0;

    // Calculate number of output elements
    for (unsigned char i = 0; i < 4; i++)
    {
        if (binary[i] == '1')
        {
            result_len++;
        }
    }

    // Allocate memory for result
    char **result = (char **)malloc((result_len + 1) * sizeof(char *));
    if (result_len == 0)
    {
        result[0] = NULL;
        free(binary);
        return (const char **)result;
    }

    // Populate result with actions
    unsigned char index = 0;
    for (unsigned char i = 0; i < 4; i++)
    {
        if (binary[i] == '1')
        {
            result[index++] = (char *)actions[i];
        }
    }

    // Reverse if needed
    if (binary[4] == '1' && result_len > 1)
    {
        for (unsigned char i = 0; i < result_len / 2; i++)
        {
            char *temp = result[i];
            result[i] = result[result_len - 1 - i];
            result[result_len - 1 - i] = temp;
        }
    }

    result[result_len] = NULL; // Null-terminate the result
    free(binary);
    return (const char **)result;
}