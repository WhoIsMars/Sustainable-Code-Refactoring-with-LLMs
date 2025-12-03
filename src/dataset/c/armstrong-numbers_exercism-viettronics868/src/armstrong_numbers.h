#ifndef ARMSTRONG_NUMBERS_H
#define ARMSTRONG_NUMBERS_H

#include <stdbool.h>
#include <stddef.h>

bool is_armstrong_number(int candidate);
void convert_number(int candidate, int *array_number, size_t *leng_of_array);

#endif
