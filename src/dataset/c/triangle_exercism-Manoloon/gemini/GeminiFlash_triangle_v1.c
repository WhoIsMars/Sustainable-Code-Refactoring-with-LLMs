#include "triangle.h"
#include <algorithm>

bool is_triangle(const triangle_t* sides) {
    if (sides->a <= 0 || sides->b <= 0 || sides->c <= 0) return false;

    // Sort sides to optimize triangle inequality check.
    int a = sides->a;
    int b = sides->b;
    int c = sides->c;

    if (a > b) std::swap(a, b);
    if (a > c) std::swap(a, c);
    if (b > c) std::swap(b, c);

    return (a + b > c);
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