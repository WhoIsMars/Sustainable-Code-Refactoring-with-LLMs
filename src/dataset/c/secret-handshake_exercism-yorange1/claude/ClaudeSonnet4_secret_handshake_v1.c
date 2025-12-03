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
    if (!cmds) return NULL;

    size_t cmd_index = 0;
    
    if (number & CMD_REVERSE) {
        // Fill in reverse order
        for (int i = 3; i >= 0; i--) {
            if (number & (1 << i)) {
                size_t len = strlen(cmd_table[i]) + 1;
                cmds[cmd_index] = (char*)malloc(len);
                if (cmds[cmd_index]) {
                    memcpy(cmds[cmd_index], cmd_table[i], len);
                }
                cmd_index++;
            }
        }
    } else {
        // Fill in normal order
        for (size_t i = 0; i < 4; i++) {
            if (number & (1 << i)) {
                size_t len = strlen(cmd_table[i]) + 1;
                cmds[cmd_index] = (char*)malloc(len);
                if (cmds[cmd_index]) {
                    memcpy(cmds[cmd_index], cmd_table[i], len);
                }
                cmd_index++;
            }
        }
    }

    return (const char**)cmds;
}