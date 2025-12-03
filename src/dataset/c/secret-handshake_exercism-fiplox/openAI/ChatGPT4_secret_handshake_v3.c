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
        size_t index = reverse ? 3 - i : i;
        if (number & (1 << i)) {
            cmds[pos++] = actions[index];
        }
    }

    return cmds;
}