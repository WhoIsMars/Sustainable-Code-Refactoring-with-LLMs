#include "triangle.h"
#include <stdio.h>
#include <stdbool.h>

bool is_triangle(triangle_t input){
    return (input.a > 0 && input.b > 0 && input.c > 0) &&
           (input.a + input.b > input.c) &&
           (input.a + input.c > input.b) &&
           (input.b + input.c > input.a);
}

bool is_scalene(triangle_t input){
    return is_triangle(input) &&
           (input.a != input.b) &&
           (input.a != input.c) &&
           (input.b != input.c);
}

bool is_isosceles(triangle_t input){
    if (!is_triangle(input)) return false;
    
    int equal_sides = 0;
    if (input.a == input.b) equal_sides++;
    if (input.a == input.c) equal_sides++;
    if (input.b == input.c) equal_sides++;
    
    return equal_sides >= 1;
}

bool is_equilateral(triangle_t input){
    return is_triangle(input) &&
           (input.a == input.b) &&
           (input.b == input.c);
}