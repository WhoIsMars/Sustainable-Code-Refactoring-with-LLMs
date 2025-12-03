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
    if (number == 0) {
        return (const char**)calloc(1, sizeof(char*));
    }

    // Count bits set in first 4 positions
    size_t count = 0;
    for (size_t i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            count++;
        }
    }

    if (count == 0) {
        return (const char**)calloc(1, sizeof(char*));
    }

    char **cmds = (char**)calloc(count + 1, sizeof(char*));
    
    if ((number & CMD_REVERSE) != 0) {
        // Fill in reverse order
        size_t idx = count - 1;
        for (size_t i = 0; i < 4; i++) {
            if (number & (1 << i)) {
                size_t len = strlen(cmd_table[i]) + 1;
                cmds[idx] = (char*)malloc(len);
                strcpy(cmds[idx], cmd_table[i]);
                idx--;
            }
        }
    } else {
        // Fill in normal order
        size_t idx = 0;
        for (size_t i = 0; i < 4; i++) {
            if (number & (1 << i)) {
                size_t len = strlen(cmd_table[i]) + 1;
                cmds[idx] = (char*)malloc(len);
                strcpy(cmds[idx], cmd_table[i]);
                idx++;
            }
        }
    }

    return (const char**)cmds;
}