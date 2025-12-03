#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails) {
    if (!text || rails <= 0) {
        return NULL;
    }

    size_t length = strlen(text);
    if (length == 0) {
        return NULL;
    }

    char *cipher = (char *)calloc(length + 1, sizeof(char));
    if (!cipher) {
        return NULL;
    }

    size_t *rail_lengths = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_lengths) {
        free(cipher);
        return NULL;
    }

    int row_step = 1;
    size_t row = 0;
    for (size_t col = 0; col < length; col++) {
        rail_lengths[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0) {
            row_step *= -1;
        }
    }

    size_t *rail_offsets = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_offsets) {
        free(cipher);
        free(rail_lengths);
        return NULL;
    }

    row_step = 1;
    row = 0;
    for (size_t col = 0; col < length; col++) {
        size_t offset = 0;
        for (size_t i = 0; i < row; ++i) {
            offset += rail_lengths[i];
        }
        cipher[offset + rail_offsets[row]] = text[col];
        rail_offsets[row]++;

        row += row_step;
        if (row == rails - 1 || row == 0) {
            row_step *= -1;
        }
    }

    free(rail_lengths);
    free(rail_offsets);

    return cipher;
}

char *decode(char *ciphertext, size_t rails) {
    if (!ciphertext || rails <= 0) {
        return NULL;
    }

    size_t length = strlen(ciphertext);
    if (length == 0) {
        return NULL;
    }

    char *text = (char *)calloc(length + 1, sizeof(char));
    if (!text) {
        return NULL;
    }

    size_t *rail_lengths = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_lengths) {
        free(text);
        return NULL;
    }

    int row_step = 1;
    size_t row = 0;
    for (size_t col = 0; col < length; col++) {
        rail_lengths[row]++;
        row += row_step;
        if (row == rails - 1 || row == 0) {
            row_step *= -1;
        }
    }

    size_t *rail_offsets = (size_t *)calloc(rails, sizeof(size_t));
    if (!rail_offsets) {
        free(text);
        free(rail_lengths);
        return NULL;
    }

    size_t cipher_index = 0;
    for (size_t i = 0; i < rails; ++i) {
        for (size_t j = 0; j < rail_lengths[i]; ++j) {
            rail_offsets[i] = cipher_index++;
        }
    }

    char *temp_cipher = (char *)calloc(length, sizeof(char));
    if (!temp_cipher) {
        free(text);
        free(rail_lengths);
        free(rail_offsets);
        return NULL;
    }

    cipher_index = 0;
    for (size_t i = 0; i < rails; ++i) {
        for (size_t j = 0; j < rail_lengths[i]; ++j) {
            temp_cipher[rail_offsets[i]] = ciphertext[cipher_index++];
        }
    }

    row_step = 1;
    row = 0;
    for (size_t col = 0; col < length; col++) {
        size_t offset = 0;
        for (size_t i = 0; i < row; ++i) {
            offset += rail_lengths[i];
        }
        text[col] = temp_cipher[offset + rail_offsets[row] - cipher_index + length];

        row += row_step;
        if (row == rails - 1 || row == 0) {
            row_step *= -1;
        }
    }

    free(rail_lengths);
    free(rail_offsets);
    free(temp_cipher);

    return text;
}