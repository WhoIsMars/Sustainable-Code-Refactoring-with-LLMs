#include "triangle.h"

int is_valid_triangle(triangle_t sides);

inline int is_valid_triangle(triangle_t sides)
{
    return (sides.a > 0 && sides.b > 0 && sides.c > 0 &&
            sides.a + sides.b > sides.c &&
            sides.b + sides.c > sides.a &&
            sides.a + sides.c > sides.b);
}

inline int is_equilateral(triangle_t sides) 
{
    return (is_valid_triangle(sides) && sides.a == sides.b && sides.b == sides.c);
}

inline int is_isosceles(triangle_t sides) 
{
    return (is_valid_triangle(sides) && 
           (sides.a == sides.b || sides.b == sides.c || sides.a == sides.c));
}

inline int is_scalene(triangle_t sides) 
{
    return (is_valid_triangle(sides) && 
           (sides.a != sides.b && sides.b != sides.c && sides.a != sides.c));
}