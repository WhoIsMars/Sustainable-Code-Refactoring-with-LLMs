#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    size_t length = strlen(text);
    if (0 == length || NULL == text || 0 == rails)
    {
        return NULL;
    }

    char *cipher = (char *)calloc(1, length + 1);
    if (NULL == cipher)
    {
        return NULL;
    }

    size_t *rail_lengths = (size_t *)calloc(rails, sizeof(size_t));
    if (NULL == rail_lengths)
    {
        free(cipher);
        return NULL;
    }

    int row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        rail_lengths[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    size_t *rail_positions = (size_t *)calloc(rails, sizeof(size_t));
    if (NULL == rail_positions)
    {
        free(cipher);
        free(rail_lengths);
        return NULL;
    }

    for (size_t i = 1; i < rails; i++)
    {
        rail_positions[i] = rail_positions[i - 1] + rail_lengths[i - 1];
    }

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        cipher[rail_positions[row]++] = text[col];
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    free(rail_lengths);
    free(rail_positions);

    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    size_t length = strlen(ciphertext);
    if (0 == length || NULL == ciphertext || 0 == rails)
    {
        return NULL;
    }

    char *text = (char *)calloc(1, length + 1);
    if (NULL == text)
    {
        return NULL;
    }

    size_t *rail_lengths = (size_t *)calloc(rails, sizeof(size_t));
    if (NULL == rail_lengths)
    {
        free(text);
        return NULL;
    }

    int row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        rail_lengths[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    size_t *rail_positions = (size_t *)calloc(rails, sizeof(size_t));
    if (NULL == rail_positions)
    {
        free(text);
        free(rail_lengths);
        return NULL;
    }

    for (size_t i = 1; i < rails; i++)
    {
        rail_positions[i] = rail_positions[i - 1] + rail_lengths[i - 1];
    }

    size_t count = 0;
    for (size_t row = 0; row < rails; row++)
    {
        for (size_t i = 0; i < rail_lengths[row]; i++)
        {
            text[rail_positions[row] + i] = ciphertext[count++];
        }
    }

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        text[col] = text[rail_positions[row]++];
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    free(rail_lengths);
    free(rail_positions);

    return text;
}