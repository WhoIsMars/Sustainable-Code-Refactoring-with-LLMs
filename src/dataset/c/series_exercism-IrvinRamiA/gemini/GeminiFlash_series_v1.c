#include "series.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    size_t len = strlen(input_text);
    slices_t result = {0};

    if (substring_length == 0 || substring_length > len) {
        result.substring = NULL;
        return result;
    }

    size_t total_substrings = len - substring_length + 1;

    /* Memory allocation for output substrings */
    result.substring = (char **)malloc(total_substrings * sizeof(char *));

    if (result.substring == NULL) {
        return result; // Handle allocation failure
    }

    for (size_t i = 0; i < total_substrings; i++)
    {
        result.substring[i] = (char *)malloc((substring_length + 1) * sizeof(char));
        if (result.substring[i] == NULL) {
            // Handle allocation failure: free previously allocated memory
            for (size_t j = 0; j < i; j++) {
                free(result.substring[j]);
            }
            free(result.substring);
            result.substring = NULL;
            return result;
        }
    }

    /* Assigning slices in output structure */
    for (size_t i = 0; i < total_substrings; i++)
    {
        strncpy(result.substring[i], input_text + i, substring_length);
        result.substring[i][substring_length] = '\0';
        result.substring_count++;
    }

    return result;
}