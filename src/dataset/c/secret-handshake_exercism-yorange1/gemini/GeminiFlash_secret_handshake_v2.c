#include "secret_handshake.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CMD_WINK (0x01)
#define CMD_DOBULE (0x02)
#define CMD_CLOSE (0x04)
#define CMD_JUMP (0x08)
#define CMD_REVERSE (0x10)
#define CMD_STR_LEN (20)

const char **commands(size_t number) {
    static const char *cmd_table[] = {
        "wink",
        "double blink",
        "close your eyes",
        "jump"
    };

    size_t count = 0;
    for (size_t i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            ++count;
        }
    }

    char **cmds = (char **)calloc(count + 1, sizeof(char *)); // Allocate space for NULL terminator
    if (!cmds) return NULL; // Handle allocation failure

    size_t index = 0;
    if (number & CMD_REVERSE) {
        for (int i = 3; i >= 0; --i) {
            if (number & (1 << i)) {
                cmds[index] = strdup(cmd_table[i]);
                if (!cmds[index]) {
                    // Handle allocation failure: free previously allocated strings
                    for (size_t j = 0; j < index; ++j) {
                        free(cmds[j]);
                    }
                    free(cmds);
                    return NULL;
                }
                ++index;
            }
        }
    } else {
        for (size_t i = 0; i < 4; ++i) {
            if (number & (1 << i)) {
                cmds[index] = strdup(cmd_table[i]);
                if (!cmds[index]) {
                    // Handle allocation failure: free previously allocated strings
                    for (size_t j = 0; j < index; ++j) {
                        free(cmds[j]);
                    }
                    free(cmds);
                    return NULL;
                }
                ++index;
            }
        }
    }

    cmds[index] = NULL; // Null-terminate the array
    return (const char **)cmds;
}