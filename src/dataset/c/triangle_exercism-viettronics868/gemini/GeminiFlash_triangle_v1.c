#include "triangle.h"
#include <stdbool.h>

bool is_triangle(triangle_t input) {
    if ((input.a <= 0) || (input.b <= 0) || (input.c <= 0)) {
        return false;
    }
    if ((input.a + input.b <= input.c) ||
        (input.a + input.c <= input.b) ||
        (input.b + input.c <= input.a)) {
        return false;
    }
    return true;
}

bool is_scalene(triangle_t input) {
    if (!is_triangle(input)) {
        return false;
    }
    return (input.a != input.b) && (input.a != input.c) && (input.b != input.c);
}

bool is_isosceles(triangle_t input) {
    if (!is_triangle(input)) {
        return false;
    }
    return (input.a == input.b) || (input.a == input.c) || (input.b == input.c);
}

bool is_equilateral(triangle_t input) {
    if (!is_triangle(input)) {
        return false;
    }
    return (input.a == input.b) && (input.b == input.c);
}