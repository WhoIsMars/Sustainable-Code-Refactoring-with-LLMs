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
    const char **cmds = (const char **)malloc(4 * sizeof(char *));
    if (!cmds) return NULL;

    for (size_t i = 0; i < 4; i++)
    {
        if (number & (1 << i))
        {
            cmds[count++] = cmd_table[i];
        }
    }

    if (number & CMD_REVERSE)
    {
        for (size_t i = 0; i < count / 2; i++)
        {
            const char *temp = cmds[i];
            cmds[i] = cmds[count - 1 - i];
            cmds[count - 1 - i] = temp;
        }
    }

    cmds = (const char **)realloc(cmds, count * sizeof(char *));
    return cmds;
}