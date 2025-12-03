#include "secret_handshake.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CMD_WINK (0x01)
#define CMD_DOUBLE_BLINK (0x02)
#define CMD_CLOSE_EYES (0x04)
#define CMD_JUMP (0x08)
#define CMD_REVERSE (0x10)
#define CMD_MAX (0x1F)

const char **commands(size_t number) {
    const char *cmd_table[] = {
        "wink",
        "double blink",
        "close your eyes",
        "jump"
    };

    size_t count = 0;
    const char *tmp_cmds[4];

    for (size_t i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            tmp_cmds[count++] = cmd_table[i];
        }
    }

    char **cmds = (char **)calloc(count + 1, sizeof(char *)); // Allocate space for NULL terminator

    if (cmds == NULL) {
        return NULL; // Handle allocation failure
    }

    if (count == 0) {
        cmds[0] = NULL; // Null-terminate the array
        return (const char **)cmds;
    }

    size_t j = 0;
    if (number & CMD_REVERSE) {
        for (size_t i = count; i > 0; i--) {
            size_t len = strlen(tmp_cmds[i - 1]);
            cmds[j] = (char *)malloc(len + 1);
            if (cmds[j] == NULL) {
                // Handle allocation failure: free previously allocated memory
                for (size_t k = 0; k < j; k++) {
                    free(cmds[k]);
                }
                free(cmds);
                return NULL;
            }
            strcpy(cmds[j], tmp_cmds[i - 1]);
            j++;
        }
    } else {
        for (size_t i = 0; i < count; i++) {
            size_t len = strlen(tmp_cmds[i]);
            cmds[j] = (char *)malloc(len + 1);
            if (cmds[j] == NULL) {
                // Handle allocation failure: free previously allocated memory
                for (size_t k = 0; k < j; k++) {
                    free(cmds[k]);
                }
                free(cmds);
                return NULL;
            }
            strcpy(cmds[j], tmp_cmds[i]);
            j++;
        }
    }

    cmds[count] = NULL; // Null-terminate the array
    return (const char **)cmds;
}