#include "secret_handshake.h"
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number) {
    char **cmds = malloc(sizeof(char*) * 4);
    if (!cmds) return NULL;

    size_t pos = 0;
    size_t i;

    for (i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            cmds[pos++] = actions[i];
        }
    }

    if (number & 16) {
        // Reverse the order of the commands
        for (i = 0; i < pos / 2; ++i) {
            char *temp = cmds[i];
            cmds[i] = cmds[pos - 1 - i];
            cmds[pos - 1 - i] = temp;
        }
    }

    // Null terminate the array if fewer than 4 commands were added
    if (pos < 4) {
        cmds[pos] = NULL;
    }

    return (const char**)cmds;
}