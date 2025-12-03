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

    size_t *rail_positions = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_positions)
    {
        free(cipher);
        return NULL;
    }

    int row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        rail_positions[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0)
            row_step *= -1;
    }

    size_t offset = 0;
    for (size_t i = 0; i < rails; i++)
    {
        size_t temp = rail_positions[i];
        rail_positions[i] = offset;
        offset += temp;
    }

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        cipher[rail_positions[row]++] = text[col];
        row += row_step;
        if (row == rails - 1 || row == 0)
            row_step *= -1;
    }

    free(rail_positions);
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

    size_t *rail_positions = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_positions)
    {
        free(text);
        return NULL;
    }

    int row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        rail_positions[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0)
            row_step *= -1;
    }

    size_t offset = 0;
    for (size_t i = 0; i < rails; i++)
    {
        size_t temp = rail_positions[i];
        rail_positions[i] = offset;
        offset += temp;
    }

    for (size_t i = 0; i < rails; i++)
    {
        for (size_t j = rail_positions[i]; j < rail_positions[i] + (i < rails - 1 ? rail_positions[i + 1] - rail_positions[i] : length - rail_positions[i]); j++)
        {
            text[j] = ciphertext[j];
        }
    }

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        text[col] = ciphertext[rail_positions[row]++];
        row += row_step;
        if (row == rails - 1 || row == 0)
            row_step *= -1;
    }

    free(rail_positions);
    return text;
}