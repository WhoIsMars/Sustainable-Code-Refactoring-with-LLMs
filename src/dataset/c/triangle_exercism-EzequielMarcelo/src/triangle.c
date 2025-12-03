#include "triangle.h"

int is_valid_triangle(triangle_t sides);

int is_valid_triangle(triangle_t sides)
{
    if (sides.a <= 0 || sides.b <= 0 || sides.c <= 0) 
        return 0;
    
    if (sides.a + sides.b < sides.c || sides.b + sides.c < sides.a || sides.a + sides.c < sides.b) 
        return 0;
    
    return 1;
}

int is_equilateral(triangle_t sides) 
{
    if (!is_valid_triangle(sides)) 
        return 0;

    return (sides.a == sides.b && sides.b == sides.c);
}

int is_isosceles(triangle_t sides) 
{
    if (!is_valid_triangle(sides)) 
        return 0;

    return (sides.a == sides.b || sides.b == sides.c || sides.a == sides.c);
}

int is_scalene(triangle_t sides) 
{
    if (!is_valid_triangle(sides)) 
        return 0;

    return (sides.a != sides.b && sides.b != sides.c && sides.a != sides.c);
}