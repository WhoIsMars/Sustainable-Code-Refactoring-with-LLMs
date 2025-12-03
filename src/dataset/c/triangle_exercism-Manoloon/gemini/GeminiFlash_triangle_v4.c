#include "triangle.h"
#include <algorithm>

bool is_triangle(const triangle_t* sides) {
    if (sides->a <= 0 || sides->b <= 0 || sides->c <= 0) return false;

    // Check triangle inequality theorem.  Avoids potential overflow.
    return (sides->a <= sides->b + sides->c) &&
           (sides->b <= sides->a + sides->c) &&
           (sides->c <= sides->a + sides->b);
}


bool is_equilateral(triangle_t sides) {
    if (!is_triangle(&sides)) return false;
    return (sides.a == sides.b) && (sides.b == sides.c);
}

bool is_isosceles(triangle_t sides) {
    if (!is_triangle(&sides)) return false;
    return (sides.a == sides.b) || (sides.a == sides.c) || (sides.b == sides.c);
}

bool is_scalene(triangle_t sides) {
    if (!is_triangle(&sides)) return false;
    return (sides.a != sides.b) && (sides.a != sides.c) && (sides.b != sides.c);
}