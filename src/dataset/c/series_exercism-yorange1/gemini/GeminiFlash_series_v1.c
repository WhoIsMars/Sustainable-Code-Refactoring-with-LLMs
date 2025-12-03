#include "series.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length) {
    assert(input_text != NULL);

    size_t len = strlen(input_text);

    if (len < substring_length || len == 0 || substring_length == 0) {
        return (slices_t){0, NULL};
    }

    size_t substring_count = len - substring_length + 1;
    char **substrings = calloc(substring_count, sizeof(char *));

    if (substrings == NULL) {
        return (slices_t){0, NULL}; // Handle allocation failure
    }

    for (size_t i = 0; i < substring_count; i++) {
        substrings[i] = malloc(substring_length + 1);
        if (substrings[i] == NULL) {
            // Handle allocation failure: free previously allocated substrings
            for (size_t j = 0; j < i; j++) {
                free(substrings[j]);
            }
            free(substrings);
            return (slices_t){0, NULL};
        }
        strncpy(substrings[i], &input_text[i], substring_length);
        substrings[i][substring_length] = '\0'; // Ensure null termination
    }

    return (slices_t){substring_count, substrings};
}