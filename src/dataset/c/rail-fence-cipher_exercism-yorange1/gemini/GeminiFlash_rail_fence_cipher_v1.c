#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails) {
    if (text == NULL || rails == 0) {
        return NULL;
    }

    size_t length = strlen(text);
    if (length == 0) {
        return NULL;
    }

    char *cipher = (char *)calloc(length + 1, sizeof(char));
    if (cipher == NULL) {
        return NULL;
    }

    size_t rail_index[length];
    int row_step = 1;
    size_t row = 0;

    for (size_t col = 0; col < length; col++) {
        rail_index[col] = row;
        row += row_step;
        if (row == rails - 1 || row == 0) {
            row_step *= -1;
        }
    }

    size_t cipher_index = 0;
    for (size_t r = 0; r < rails; r++) {
        for (size_t i = 0; i < length; i++) {
            if (rail_index[i] == r) {
                cipher[cipher_index++] = text[i];
            }
        }
    }

    return cipher;
}

char *decode(char *ciphertext, size_t rails) {
    if (ciphertext == NULL || rails == 0) {
        return NULL;
    }

    size_t length = strlen(ciphertext);
    if (length == 0) {
        return NULL;
    }

    char *text = (char *)calloc(length + 1, sizeof(char));
    if (text == NULL) {
        return NULL;
    }

    size_t rail_index[length];
    int row_step = 1;
    size_t row = 0;

    for (size_t col = 0; col < length; col++) {
        rail_index[col] = row;
        row += row_step;
        if (row == rails - 1 || row == 0) {
            row_step *= -1;
        }
    }

    size_t rail_count[rails];
    memset(rail_count, 0, sizeof(rail_count));
    for (size_t i = 0; i < length; i++) {
        rail_count[rail_index[i]]++;
    }

    size_t rail_start[rails];
    rail_start[0] = 0;
    for (size_t r = 1; r < rails; r++) {
        rail_start[r] = rail_start[r - 1] + rail_count[r - 1];
    }

    char temp_cipher[length];
    strcpy(temp_cipher, ciphertext);

    for (size_t i = 0; i < length; i++) {
        size_t rail = rail_index[i];
        text[i] = temp_cipher[rail_start[rail]++];
    }

    return text;
}