#ifndef PROCESS_LONG_INPUT_H
#define PROCESS_LONG_INPUT_H

#include <stdlib.h>

int parse_input(int fd, size_t chunk_size, char **complete_message);

#endif