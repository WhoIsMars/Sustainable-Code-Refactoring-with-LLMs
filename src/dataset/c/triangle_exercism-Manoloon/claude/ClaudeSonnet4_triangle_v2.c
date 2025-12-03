#include "triangle.h"

bool is_triangle(const triangle_t* sides)
{
    if(sides->a <= 0 || sides->b <= 0 || sides->c <= 0) return false;
    return (sides->a + sides->b > sides->c) && 
           (sides->b + sides->c > sides->a) && 
           (sides->a + sides->c > sides->b);
}

bool is_equilateral(triangle_t sides)
{
    if(sides.a <= 0 || sides.b <= 0 || sides.c <= 0) return false;
    if(sides.a != sides.b || sides.a != sides.c) return false;
    return (sides.a + sides.b > sides.c);
}

bool is_isosceles(triangle_t sides)
{
    if(sides.a <= 0 || sides.b <= 0 || sides.c <= 0) return false;
    
    bool ab_equal = (sides.a == sides.b);
    bool ac_equal = (sides.a == sides.c);
    bool bc_equal = (sides.b == sides.c);
    
    if(!ab_equal && !ac_equal && !bc_equal) return false;
    
    return (sides.a + sides.b > sides.c) && 
           (sides.b + sides.c > sides.a) && 
           (sides.a + sides.c > sides.b);
}

bool is_scalene(triangle_t sides)
{
    if(sides.a <= 0 || sides.b <= 0 || sides.c <= 0) return false;
    if(sides.a == sides.b || sides.a == sides.c || sides.b == sides.c) return false;
    return (sides.a + sides.b > sides.c) && 
           (sides.b + sides.c > sides.a) && 
           (sides.a + sides.c > sides.b);
}