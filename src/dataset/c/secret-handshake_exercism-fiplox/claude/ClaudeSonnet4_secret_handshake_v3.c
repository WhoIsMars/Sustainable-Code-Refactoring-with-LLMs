#include "secret_handshake.h"
#include <string.h>
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	char **cmds = calloc(5, sizeof(char*));
	size_t pos = 0;
	const size_t reverse = number & 16;
	
	if (reverse) {
		for (size_t i = 4; i-- > 0;) {
			if (number & (1 << i)) {
				cmds[pos++] = (char*)actions[i];
			}
		}
	} else {
		for (size_t i = 0; i < 4; ++i) {
			if (number & (1 << i)) {
				cmds[pos++] = (char*)actions[i];
			}
		}
	}
	
	return (const char**)cmds;
}