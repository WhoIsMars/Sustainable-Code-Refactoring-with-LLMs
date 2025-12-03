#include "crypto_square.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *ciphertext(const char *input)
{
    assert(input != NULL);

    size_t input_len = strlen(input);
    char *normalized = (char *)malloc(input_len + 1);
    size_t index = 0;

    for (size_t i = 0; i < input_len; i++)
    {
        if (isalnum(input[i]))
        {
            normalized[index++] = tolower(input[i]);
        }
    }
    normalized[index] = '\0';

    size_t cols = ceil(sqrt((float)index));
    size_t rows = (cols * (cols - 1) >= index) ? cols - 1 : cols;

    char *cipher = (char *)malloc((rows + 1) * cols + 1);
    size_t cipher_index = 0;

    for (size_t col = 0; col < cols; col++)
    {
        for (size_t row = 0; row < rows; row++)
        {
            size_t pos = row * cols + col;
            if (pos < index)
            {
                cipher[cipher_index++] = normalized[pos];
            }
            else
            {
                break;
            }
        }
        if (col < cols - 1)
        {
            cipher[cipher_index++] = ' ';
        }
    }
    cipher[cipher_index] = '\0';

    free(normalized);
    return cipher;
}