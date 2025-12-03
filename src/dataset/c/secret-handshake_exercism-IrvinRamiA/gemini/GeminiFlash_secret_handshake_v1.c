#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char **commands(size_t number) {
    const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    size_t result_len = 0;
    const char **result = malloc(5 * sizeof(char *)); // Max 4 commands + NULL terminator
    size_t index = 0;

    for (int i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            result[index++] = actions[i];
            result_len++;
        }
    }

    if (number & (1 << 4)) {
        // Reverse the array
        for (size_t i = 0; i < result_len / 2; ++i) {
            const char *temp = result[i];
            result[i] = result[result_len - 1 - i];
            result[result_len - 1 - i] = temp;
        }
    }

    if (result_len == 0) {
        free(result);
        const char **empty_result = malloc(sizeof(char*));
        empty_result[0] = NULL;
        return (const char **)empty_result;
    }

    result[index] = NULL; // Null-terminate the array
    return (const char **)result;
}