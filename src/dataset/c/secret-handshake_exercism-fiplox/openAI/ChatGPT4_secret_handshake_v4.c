#include "secret_handshake.h"
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
    const char **cmds = malloc(4 * sizeof(char*));
    size_t pos = 0;

    if (!cmds) return NULL;

    for (size_t i = 0; i < 4; ++i) {
        size_t n = (number & 16) ? (3 - i) : i;
        if (number & (1 << n)) {
            cmds[pos++] = actions[n];
        }
    }

    cmds = realloc(cmds, pos * sizeof(char*));
    return cmds;
}