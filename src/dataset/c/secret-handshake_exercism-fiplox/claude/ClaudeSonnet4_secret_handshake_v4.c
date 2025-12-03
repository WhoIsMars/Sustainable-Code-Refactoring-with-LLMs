#include "secret_handshake.h"
#include <string.h>
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	const char **cmds = calloc(5, sizeof(const char*));
	size_t pos = 0;
	
	if (number & 16) {
		if (number & 8) cmds[pos++] = actions[3];
		if (number & 4) cmds[pos++] = actions[2];
		if (number & 2) cmds[pos++] = actions[1];
		if (number & 1) cmds[pos++] = actions[0];
	} else {
		if (number & 1) cmds[pos++] = actions[0];
		if (number & 2) cmds[pos++] = actions[1];
		if (number & 4) cmds[pos++] = actions[2];
		if (number & 8) cmds[pos++] = actions[3];
	}
	
	return cmds;
}