#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>

const char **commands(size_t number) {
    const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    size_t result_len = 0;
    const char **result_temp = malloc(5 * sizeof(char *)); // Max 4 actions + NULL terminator
    if (!result_temp) return NULL;

    for (size_t i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            result_temp[result_len++] = actions[i];
        }
    }

    if (number & 16) {
        // Reverse the array
        for (size_t i = 0; i < result_len / 2; ++i) {
            const char *temp = result_temp[i];
            result_temp[i] = result_temp[result_len - 1 - i];
            result_temp[result_len - 1 - i] = temp;
        }
    }

    const char **result = malloc((result_len + 1) * sizeof(char *));
    if (!result) {
        free(result_temp);
        return NULL;
    }

    memcpy(result, result_temp, result_len * sizeof(char*));
    result[result_len] = NULL;

    free(result_temp);
    return result;
}