#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char **commands(size_t number) {
    const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    size_t result_len = 0;
    const char **result = NULL;
    size_t i, j;

    // Determine the number of actions
    for (i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            result_len++;
        }
    }

    // Allocate memory for the result
    if (result_len > 0) {
        result = (const char **)malloc(result_len * sizeof(char *));
        if (result == NULL) {
            return NULL; // Handle memory allocation failure
        }
    } else {
        result = (const char **)malloc(sizeof(char *));
        if (result == NULL) return NULL;
        result[0] = NULL;
        return result;
    }


    // Populate the result array
    j = 0;
    for (i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            result[j++] = actions[i];
        }
    }

    // Reverse the order if the fifth bit is set
    if (number & 16) {
        for (i = 0; i < result_len / 2; ++i) {
            const char *temp = result[i];
            result[i] = result[result_len - 1 - i];
            result[result_len - 1 - i] = temp;
        }
    }

    return result;
}