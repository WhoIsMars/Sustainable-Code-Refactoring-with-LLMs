#include "triangle.h"
#include <stdbool.h>

static inline bool is_positive(double a, double b, double c) {
    return (a > 0) && (b > 0) && (c > 0);
}

static inline bool satisfies_triangle_inequality(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

bool is_triangle(triangle_t input) {
    return is_positive(input.a, input.b, input.c) && satisfies_triangle_inequality(input.a, input.b, input.c);
}

bool is_scalene(triangle_t input) {
    return is_triangle(input) && (input.a != input.b) && (input.a != input.c) && (input.b != input.c);
}

bool is_isosceles(triangle_t input) {
    return is_triangle(input) && 
           ((input.a == input.b) || (input.a == input.c) || (input.b == input.c));
}

bool is_equilateral(triangle_t input) {
    return is_triangle(input) && (input.a == input.b) && (input.b == input.c);
}