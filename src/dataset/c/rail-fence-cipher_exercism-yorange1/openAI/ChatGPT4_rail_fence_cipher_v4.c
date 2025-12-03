#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    if (!text || rails == 0)
        return NULL;

    size_t length = strlen(text);
    if (length == 0)
        return NULL;

    char *cipher = (char *)calloc(length + 1, sizeof(char));
    if (!cipher)
        return NULL;

    size_t *rail_lengths = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_lengths)
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
            row_step *= -1;
    }

    size_t *rail_offsets = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_offsets)
    {
        free(cipher);
        free(rail_lengths);
        return NULL;
    }

    for (size_t i = 1; i < rails; i++)
        rail_offsets[i] = rail_offsets[i - 1] + rail_lengths[i - 1];

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        cipher[rail_offsets[row]++] = text[col];
        row += row_step;
        if (row == rails - 1 || row == 0)
            row_step *= -1;
    }

    free(rail_lengths);
    free(rail_offsets);
    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    if (!ciphertext || rails == 0)
        return NULL;

    size_t length = strlen(ciphertext);
    if (length == 0)
        return NULL;

    char *text = (char *)calloc(length + 1, sizeof(char));
    if (!text)
        return NULL;

    size_t *rail_lengths = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_lengths)
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
            row_step *= -1;
    }

    size_t *rail_offsets = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_offsets)
    {
        free(text);
        free(rail_lengths);
        return NULL;
    }

    for (size_t i = 1; i < rails; i++)
        rail_offsets[i] = rail_offsets[i - 1] + rail_lengths[i - 1];

    size_t count = 0;
    for (size_t row = 0; row < rails; row++)
    {
        for (size_t i = 0; i < rail_lengths[row]; i++)
            text[rail_offsets[row]++] = ciphertext[count++];
    }

    free(rail_lengths);
    free(rail_offsets);

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        text[col] = text[rail_offsets[row] - rail_lengths[row]];
        rail_lengths[row]--;
        row += row_step;
        if (row == rails - 1 || row == 0)
            row_step *= -1;
    }

    return text;
}