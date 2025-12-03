#include "triangle.h"

bool is_equilateral(triangle_t sides)
{
    if(!is_triangle(&sides)) return false;
    return (sides.a == sides.b) && (sides.a == sides.c);
}

bool is_isosceles(triangle_t sides)
{
    if(!is_triangle(&sides)) return false;
    return (sides.a == sides.b) || (sides.a == sides.c) || (sides.b == sides.c);
}

bool is_scalene(triangle_t sides)
{
    if(!is_triangle(&sides)) return false;
    return (sides.a != sides.b) && (sides.b != sides.c) && (sides.a != sides.c);
}

bool is_triangle(const triangle_t* sides)
{
    if(sides->a == 0 || sides->b == 0 || sides->c == 0) return false;
    bool equiA = sides->a + sides->b >= sides->c;
    bool equiB = sides->b + sides->c >= sides->a;
    bool equiC = sides->a + sides->c >= sides->b;
    return equiA && equiB && equiC;
}
