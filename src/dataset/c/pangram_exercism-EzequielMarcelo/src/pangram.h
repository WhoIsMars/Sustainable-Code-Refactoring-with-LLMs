#ifndef PANGRAM_H
#define PANGRAM_H

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

#define ALPHABET_COUNT 26

bool is_pangram(const char *sentence);

#endif
