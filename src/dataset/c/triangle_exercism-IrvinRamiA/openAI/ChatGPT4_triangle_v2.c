#include "triangle.h"

static inline bool complies_triangle_inequality(const triangle_t triangle)
{
    return (triangle.a + triangle.b > triangle.c &&
            triangle.b + triangle.c > triangle.a &&
            triangle.c + triangle.a > triangle.b);
}

bool is_equilateral(const triangle_t triangle)
{
    return (triangle.a == triangle.b && triangle.b == triangle.c && triangle.a != 0);
}

bool is_scalene(const triangle_t triangle)
{
    return (triangle.a != triangle.b &&
            triangle.b != triangle.c &&
            triangle.c != triangle.a &&
            complies_triangle_inequality(triangle));
}

bool is_isosceles(const triangle_t triangle)
{
    return (complies_triangle_inequality(triangle) &&
            (triangle.a == triangle.b || triangle.b == triangle.c || triangle.c == triangle.a));
}