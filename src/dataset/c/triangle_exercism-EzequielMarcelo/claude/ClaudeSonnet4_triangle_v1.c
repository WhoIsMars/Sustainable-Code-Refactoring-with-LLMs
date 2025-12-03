#include "triangle.h"

int is_valid_triangle(triangle_t sides)
{
    // Early exit for non-positive sides
    if (sides.a <= 0 || sides.b <= 0 || sides.c <= 0) 
        return 0;
    
    // Triangle inequality check - optimized order
    return (sides.a + sides.b > sides.c && 
            sides.b + sides.c > sides.a && 
            sides.a + sides.c > sides.b);
}

int is_equilateral(triangle_t sides) 
{
    // Early exit for non-positive sides (inlined validation)
    if (sides.a <= 0 || sides.b <= 0 || sides.c <= 0) 
        return 0;
    
    // Check equality first (faster than triangle inequality for equilateral)
    if (sides.a != sides.b || sides.b != sides.c)
        return 0;
    
    // For equilateral triangles, only need one inequality check
    return (sides.a + sides.b > sides.c);
}

int is_isosceles(triangle_t sides) 
{
    // Early exit for non-positive sides
    if (sides.a <= 0 || sides.b <= 0 || sides.c <= 0) 
        return 0;
    
    // Check triangle inequality
    if (sides.a + sides.b <= sides.c || 
        sides.b + sides.c <= sides.a || 
        sides.a + sides.c <= sides.b)
        return 0;
    
    // Check for at least two equal sides
    return (sides.a == sides.b || sides.b == sides.c || sides.a == sides.c);
}

int is_scalene(triangle_t sides) 
{
    // Early exit for non-positive sides
    if (sides.a <= 0 || sides.b <= 0 || sides.c <= 0) 
        return 0;
    
    // Check for any equal sides first (cheaper than triangle inequality)
    if (sides.a == sides.b || sides.b == sides.c || sides.a == sides.c)
        return 0;
    
    // Check triangle inequality
    return (sides.a + sides.b > sides.c && 
            sides.b + sides.c > sides.a && 
            sides.a + sides.c > sides.b);
}