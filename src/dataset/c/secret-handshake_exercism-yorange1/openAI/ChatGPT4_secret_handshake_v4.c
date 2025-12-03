#include "secret_handshake.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CMD_WINK (0x01)
#define CMD_DOUBLE (0x02)
#define CMD_CLOSE (0x04)
#define CMD_JUMP (0x08)
#define CMD_REVERSE (0x10)

const char **commands(size_t number)
{
    static const char *cmd_table[] = {
        "wink",
        "double blink",
        "close your eyes",
        "jump"
    };

    size_t count = 0;
    for (size_t i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            count++;
        }
    }

    const char **cmds = (const char **)calloc(count + 1, sizeof(char *));
    if (!cmds) {
        return NULL;
    }

    size_t index = 0;
    if (number & CMD_REVERSE) {
        for (int i = 3; i >= 0; i--) {
            if (number & (1 << i)) {
                cmds[index++] = cmd_table[i];
            }
        }
    } else {
        for (size_t i = 0; i < 4; i++) {
            if (number & (1 << i)) {
                cmds[index++] = cmd_table[i];
            }
        }
    }

    return cmds;
}