#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline size_t get_rail_position(size_t col, size_t rails) {
    if (rails == 1) return 0;
    size_t cycle = 2 * (rails - 1);
    size_t pos = col % cycle;
    return pos < rails ? pos : cycle - pos;
}

char *encode(char *text, size_t rails)
{
    if (!text || rails == 0) return NULL;
    
    size_t length = strlen(text);
    if (length == 0) return NULL;
    
    if (rails == 1) {
        char *result = malloc(length + 1);
        if (!result) return NULL;
        memcpy(result, text, length + 1);
        return result;
    }

    char *cipher = malloc(length + 1);
    if (!cipher) return NULL;
    
    size_t write_pos = 0;
    
    for (size_t rail = 0; rail < rails; rail++) {
        for (size_t col = 0; col < length; col++) {
            if (get_rail_position(col, rails) == rail) {
                cipher[write_pos++] = text[col];
            }
        }
    }
    
    cipher[length] = '\0';
    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    if (!ciphertext || rails == 0) return NULL;
    
    size_t length = strlen(ciphertext);
    if (length == 0) return NULL;
    
    if (rails == 1) {
        char *result = malloc(length + 1);
        if (!result) return NULL;
        memcpy(result, ciphertext, length + 1);
        return result;
    }

    size_t *rail_counts = calloc(rails, sizeof(size_t));
    if (!rail_counts) return NULL;
    
    for (size_t col = 0; col < length; col++) {
        rail_counts[get_rail_position(col, rails)]++;
    }
    
    char *text = malloc(length + 1);
    if (!text) {
        free(rail_counts);
        return NULL;
    }
    
    size_t cipher_pos = 0;
    size_t *rail_starts = malloc(rails * sizeof(size_t));
    if (!rail_starts) {
        free(rail_counts);
        free(text);
        return NULL;
    }
    
    rail_starts[0] = 0;
    for (size_t i = 1; i < rails; i++) {
        rail_starts[i] = rail_starts[i-1] + rail_counts[i-1];
    }
    
    for (size_t col = 0; col < length; col++) {
        size_t rail = get_rail_position(col, rails);
        text[col] = ciphertext[rail_starts[rail]++];
    }
    
    text[length] = '\0';
    
    free(rail_counts);
    free(rail_starts);
    return text;
}