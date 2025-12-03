#include "series.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length) {
    if (input_text == NULL) {
        return (slices_t){0, NULL};
    }

    size_t len = strlen(input_text);

    if (len < substring_length || len == 0 || substring_length == 0) {
        return (slices_t){0, NULL};
    }

    slices_t result = {0};
    result.substring_count = len - substring_length + 1;
    result.substring = malloc(result.substring_count * sizeof(char *));

    if (result.substring == NULL) {
        return (slices_t){0, NULL};
    }

    for (size_t i = 0; i < result.substring_count; i++) {
        result.substring[i] = malloc(substring_length + 1);
        if (result.substring[i] == NULL) {
            // Handle allocation failure: free previously allocated substrings
            for (size_t j = 0; j < i; j++) {
                free(result.substring[j]);
            }
            free(result.substring);
            return (slices_t){0, NULL};
        }
        strncpy(result.substring[i], input_text + i, substring_length);
        result.substring[i][substring_length] = '\0'; // Ensure null termination
    }

    return result;
}