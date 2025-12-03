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
#define CMD_MAX (0x1F)

const char **commands(size_t number) {
    const char *cmd_table[] = {
        "wink",
        "double blink",
        "close your eyes",
        "jump"
    };

    size_t count = 0;
    for (size_t i = 0; i < 4; i++) {
        if ((number & (1 << i)) != 0) {
            count++;
        }
    }

    char **cmds = (char **)calloc(count + 1, sizeof(char *));
    if (cmds == NULL) {
        return NULL;
    }
    cmds[count] = NULL;

    size_t index = 0;
    if ((number & CMD_REVERSE) != 0) {
        for (int i = 3; i >= 0; i--) {
            if ((number & (1 << i)) != 0) {
                size_t len = strlen(cmd_table[i]);
                cmds[index] = (char *)malloc(len + 1);
                if (cmds[index] == NULL) {
                    for (size_t j = 0; j < index; j++) {
                        free(cmds[j]);
                    }
                    free(cmds);
                    return NULL;
                }
                strcpy(cmds[index], cmd_table[i]);
                index++;
            }
        }
    } else {
        for (size_t i = 0; i < 4; i++) {
            if ((number & (1 << i)) != 0) {
                size_t len = strlen(cmd_table[i]);
                cmds[index] = (char *)malloc(len + 1);
                if (cmds[index] == NULL) {
                    for (size_t j = 0; j < index; j++) {
                        free(cmds[j]);
                    }
                    free(cmds);
                    return NULL;
                }
                strcpy(cmds[index], cmd_table[i]);
                index++;
            }
        }
    }

    return (const char**)cmds;
}