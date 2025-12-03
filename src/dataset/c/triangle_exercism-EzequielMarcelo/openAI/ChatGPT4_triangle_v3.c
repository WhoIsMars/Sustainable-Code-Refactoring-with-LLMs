#include "triangle.h"

static inline int is_positive(int a, int b, int c) {
    return (a > 0 && b > 0 && c > 0);
}

static inline int satisfies_triangle_inequality(int a, int b, int c) {
    return (a + b > c && b + c > a && a + c > b);
}

int is_valid_triangle(triangle_t sides) {
    return is_positive(sides.a, sides.b, sides.c) && satisfies_triangle_inequality(sides.a, sides.b, sides.c);
}

int is_equilateral(triangle_t sides) {
    return is_valid_triangle(sides) && (sides.a == sides.b && sides.b == sides.c);
}

int is_isosceles(triangle_t sides) {
    return is_valid_triangle(sides) && (sides.a == sides.b || sides.b == sides.c || sides.a == sides.c);
}

int is_scalene(triangle_t sides) {
    return is_valid_triangle(sides) && (sides.a != sides.b && sides.b != sides.c && sides.a != sides.c);
}