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

static const char* const cmd_table[4] = {
    "wink",
    "double blink",
    "close your eyes",
    "jump"
};

const char **commands(size_t number)
{
    if (number > 0x1F) {
        return (const char**)calloc(1, sizeof(char*));
    }

    size_t count = 0;
    size_t indices[4];
    
    for (size_t i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            indices[count++] = i;
        }
    }

    if (count == 0) {
        return (const char**)calloc(1, sizeof(char*));
    }

    char **cmds = (char**)calloc(count + 1, sizeof(char*));
    if (!cmds) {
        return NULL;
    }

    if (number & CMD_REVERSE) {
        for (size_t i = 0; i < count; i++) {
            size_t idx = indices[count - 1 - i];
            size_t len = strlen(cmd_table[idx]) + 1;
            cmds[i] = (char*)malloc(len);
            if (cmds[i]) {
                memcpy(cmds[i], cmd_table[idx], len);
            }
        }
    } else {
        for (size_t i = 0; i < count; i++) {
            size_t idx = indices[i];
            size_t len = strlen(cmd_table[idx]) + 1;
            cmds[i] = (char*)malloc(len);
            if (cmds[i]) {
                memcpy(cmds[i], cmd_table[idx], len);
            }
        }
    }

    return (const char**)cmds;
}