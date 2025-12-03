#include "triangle.h"
#include <stdio.h>
#include <stdbool.h>

double sum(double x, double y){
    return x + y;
}

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
    
    bool ab_equal = (input.a == input.b);
    bool ac_equal = (input.a == input.c);
    bool bc_equal = (input.b == input.c);
    
    return ab_equal || ac_equal || bc_equal;
}

bool is_equilateral(triangle_t input){
    return is_triangle(input) &&
           (input.a == input.b) &&
           (input.b == input.c);
}