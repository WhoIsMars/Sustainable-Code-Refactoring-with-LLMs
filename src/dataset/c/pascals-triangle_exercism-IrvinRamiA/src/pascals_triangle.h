#ifndef PASCALS_TRIANGLE_H
#define PASCALS_TRIANGLE_H

#include <stddef.h>
#include <stdint.h>

void free_triangle(uint8_t **triangle, uint8_t rows);
uint8_t **create_triangle(uint8_t rows);

#endif
