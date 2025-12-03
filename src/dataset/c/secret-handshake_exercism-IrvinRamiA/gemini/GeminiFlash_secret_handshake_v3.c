#include "secret_handshake.h"
#include <stdlib.h>
#include <string.h>

const char **commands(size_t number) {
    const char *actions[] = {"wink", "double blink", "close your eyes", "jump"};
    size_t result_len = 0;
    const char **result = NULL;
    size_t i, j;

    // Count the number of actions
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

        j = 0;
        for (i = 0; i < 4; ++i) {
            if (number & (1 << i)) {
                result[j++] = actions[i];
            }
        }

        // Reverse the order if the 5th bit is set
        if (number & (1 << 4)) {
            for (i = 0; i < result_len / 2; ++i) {
                const char *temp = result[i];
                result[i] = result[result_len - 1 - i];
                result[result_len - 1 - i] = temp;
            }
        }
    } else {
        result = (const char **)malloc(sizeof(char *));
        if(result != NULL){
            result[0] = NULL;
        }
    }

    return result;
}