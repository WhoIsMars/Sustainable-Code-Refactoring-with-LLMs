#include "triangle.h"
#include <stdbool.h>

bool is_triangle(triangle_t input) {
    return (input.a > 0 && input.b > 0 && input.c > 0 &&
            input.a + input.b > input.c &&
            input.a + input.c > input.b &&
            input.b + input.c > input.a);
}

bool is_scalene(triangle_t input) {
    return is_triangle(input) &&
           (input.a != input.b && input.a != input.c && input.b != input.c);
}

bool is_isosceles(triangle_t input) {
    return is_triangle(input) &&
           ((input.a == input.b || input.a == input.c || input.b == input.c));
}

bool is_equilateral(triangle_t input) {
    return is_triangle(input) &&
           (input.a == input.b && input.b == input.c);
}