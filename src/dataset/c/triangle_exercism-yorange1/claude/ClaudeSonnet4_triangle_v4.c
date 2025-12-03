#include "triangle.h"

#include <float.h>
#include <math.h>

static inline bool is_same(double a, double b)
{
    return fabs(a - b) < DBL_EPSILON;
}

static inline bool is_triangle(triangle_t sides)
{
    return (sides.a > 0.0 && sides.b > 0.0 && sides.c > 0.0) &&
           (sides.a + sides.b > sides.c) &&
           (sides.a + sides.c > sides.b) &&
           (sides.b + sides.c > sides.a);
}

bool is_equilateral(triangle_t sides)
{
    return is_triangle(sides) && 
           is_same(sides.a, sides.b) && 
           is_same(sides.a, sides.c);
}

bool is_isosceles(triangle_t sides)
{
    return is_triangle(sides) && 
           (is_same(sides.a, sides.b) || 
            is_same(sides.a, sides.c) || 
            is_same(sides.b, sides.c));
}

bool is_scalene(triangle_t sides)
{
    return is_triangle(sides) && 
           !is_same(sides.a, sides.b) && 
           !is_same(sides.a, sides.c) && 
           !is_same(sides.b, sides.c);
}