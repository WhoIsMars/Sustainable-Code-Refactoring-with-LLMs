#include "secret_handshake.h"
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
    const char **cmds = calloc(4, sizeof(char*));
    if (!cmds) return NULL;

    size_t pos = 0;
    int reverse = number & 16;

    for (size_t i = 0; i < 4; ++i) {
        if (number & (1 << i)) {
            cmds[reverse ? 3 - pos : pos] = actions[i];
            ++pos;
        }
    }

    return cmds;
}