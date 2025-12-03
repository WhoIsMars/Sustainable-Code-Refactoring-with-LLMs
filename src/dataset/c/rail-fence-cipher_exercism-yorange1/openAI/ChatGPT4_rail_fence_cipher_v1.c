#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    size_t length = strlen(text);
    if (length == 0 || text == NULL || rails == 0)
    {
        return NULL;
    }

    char *cipher = (char *)calloc(1, length + 1);
    if (cipher == NULL)
    {
        return NULL;
    }

    size_t *row_positions = (size_t *)calloc(rails, sizeof(size_t));
    if (row_positions == NULL)
    {
        free(cipher);
        return NULL;
    }

    int row_step = 1;
    size_t row = 0;
    for (size_t col = 0; col < length; col++)
    {
        row_positions[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    size_t *row_offsets = (size_t *)calloc(rails, sizeof(size_t));
    if (row_offsets == NULL)
    {
        free(cipher);
        free(row_positions);
        return NULL;
    }

    for (size_t i = 1; i < rails; i++)
    {
        row_offsets[i] = row_offsets[i - 1] + row_positions[i - 1];
    }

    row_step = 1;
    row = 0;
    for (size_t col = 0; col < length; col++)
    {
        cipher[row_offsets[row]++] = text[col];
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    free(row_positions);
    free(row_offsets);
    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    size_t length = strlen(ciphertext);
    if (length == 0 || ciphertext == NULL || rails == 0)
    {
        return NULL;
    }

    char *text = (char *)calloc(1, length + 1);
    if (text == NULL)
    {
        return NULL;
    }

    size_t *row_positions = (size_t *)calloc(rails, sizeof(size_t));
    if (row_positions == NULL)
    {
        free(text);
        return NULL;
    }

    int row_step = 1;
    size_t row = 0;
    for (size_t col = 0; col < length; col++)
    {
        row_positions[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    size_t *row_offsets = (size_t *)calloc(rails, sizeof(size_t));
    if (row_offsets == NULL)
    {
        free(text);
        free(row_positions);
        return NULL;
    }

    for (size_t i = 1; i < rails; i++)
    {
        row_offsets[i] = row_offsets[i - 1] + row_positions[i - 1];
    }

    size_t count = 0;
    for (size_t i = 0; i < rails; i++)
    {
        for (size_t j = 0; j < row_positions[i]; j++)
        {
            text[row_offsets[i] + j] = ciphertext[count++];
        }
    }

    row_step = 1;
    row = 0;
    for (size_t col = 0; col < length; col++)
    {
        text[col] = text[row_offsets[row]++];
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    free(row_positions);
    free(row_offsets);
    return text;
}