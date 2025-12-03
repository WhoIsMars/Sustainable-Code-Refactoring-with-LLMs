#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails) {
    if (!text || !rails) return NULL;

    size_t length = strlen(text);
    if (!length) return NULL;

    char *cipher = (char *)calloc(length + 1, sizeof(char));
    if (!cipher) return NULL;

    size_t *rail_indices = (size_t *)malloc(rails * sizeof(size_t));
    if (!rail_indices) {
        free(cipher);
        return NULL;
    }
    for (size_t i = 0; i < rails; ++i) {
        rail_indices[i] = 0;
    }

    size_t current_rail = 0;
    int direction = 1; // 1 for down, -1 for up

    for (size_t i = 0; i < length; ++i) {
        size_t index = 0;
        for(size_t j = 0; j < current_rail; ++j){
            index += rail_indices[j];
        }
        cipher[index + rail_indices[current_rail]] = text[i];
        rail_indices[current_rail]++;

        current_rail += direction;

        if (current_rail == rails) {
            current_rail = rails - 2;
            direction = -1;
        } else if (current_rail == (size_t)-1) {
            current_rail = 1;
            direction = 1;
        }
    }
    
    size_t cipher_index = 0;
    char *result = (char*)calloc(length + 1, sizeof(char));
    if(!result){
        free(cipher);
        free(rail_indices);
        return NULL;
    }
    for(size_t i = 0; i < rails; ++i){
        for(size_t j = 0; j < rail_indices[i]; ++j){
            size_t index = 0;
            for(size_t k = 0; k < i; ++k){
                index += rail_indices[k];
            }
            result[cipher_index++] = cipher[index + j];
        }
    }

    free(cipher);
    free(rail_indices);
    return result;
}

char *decode(char *ciphertext, size_t rails) {
    if (!ciphertext || !rails) return NULL;

    size_t length = strlen(ciphertext);
    if (!length) return NULL;

    char *text = (char *)calloc(length + 1, sizeof(char));
    if (!text) return NULL;

    size_t *rail_lengths = (size_t *)malloc(rails * sizeof(size_t));
    if (!rail_lengths) {
        free(text);
        return NULL;
    }
    for (size_t i = 0; i < rails; ++i) {
        rail_lengths[i] = 0;
    }

    size_t current_rail = 0;
    int direction = 1;

    for (size_t i = 0; i < length; ++i) {
        rail_lengths[current_rail]++;
        current_rail += direction;

        if (current_rail == rails) {
            current_rail = rails - 2;
            direction = -1;
        } else if (current_rail == (size_t)-1) {
            current_rail = 1;
            direction = 1;
        }
    }

    size_t *rail_indices = (size_t *)malloc(rails * sizeof(size_t));
    if (!rail_indices) {
        free(text);
        free(rail_lengths);
        return NULL;
    }
    for (size_t i = 0; i < rails; ++i) {
        rail_indices[i] = 0;
    }

    size_t cipher_index = 0;
    for (size_t i = 0; i < rails; ++i) {
        for (size_t j = 0; j < rail_lengths[i]; ++j) {
            size_t index = 0;
            for(size_t k = 0; k < i; ++k){
                index += rail_lengths[k];
            }
            text[index + j] = ciphertext[cipher_index++];
        }
    }

    current_rail = 0;
    direction = 1;
    char *result = (char*)calloc(length + 1, sizeof(char));
    if(!result){
        free(text);
        free(rail_lengths);
        free(rail_indices);
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t index = 0;
        for(size_t j = 0; j < current_rail; ++j){
            index += rail_lengths[j];
        }
        result[i] = text[index + rail_indices[current_rail]];
        rail_indices[current_rail]++;

        current_rail += direction;

        if (current_rail == rails) {
            current_rail = rails - 2;
            direction = -1;
        } else if (current_rail == (size_t)-1) {
            current_rail = 1;
            direction = 1;
        }
    }

    free(text);
    free(rail_lengths);
    free(rail_indices);
    return result;
}