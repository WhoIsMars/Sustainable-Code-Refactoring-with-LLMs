#include "triangle.h"
#include <stdio.h>
#include <stdbool.h>
double sum(double x, double y){
    return x + y;
}

bool is_triangle(triangle_t input){
    double (*add)(double x, double y) = sum;
    if ((add(input.a, input.b) >= input.c) &&
        (add(input.a, input.c) >= input.b) &&
        (add(input.b, input.c) >= input.a) &&
        (input.a > 0) && (input.b > 0) && (input.c > 0) ) {
            return true;
    } else return false; 

}

bool is_scalene(triangle_t input){
    if (is_triangle(input)){
        if ((input.a != input.b) &&
            (input.a != input.c) &&
            (input.b != input.c)){
                return true;
        } else return false;
    } else return false;
}

bool is_isosceles(triangle_t input){
    if (is_triangle(input)){
        if (((input.a == input.b) && (input.b != input.c)) || 
            ((input.a == input.c) && (input.a != input.b)) || 
            ((input.b == input.c) && (input.c != input.a)) ||
            ((input.a == input.b) && (input.b == input.c))){
                return 1;
        } else return 0;
    } else return 0;
}

bool is_equilateral(triangle_t input){
    if (is_triangle(input)){
        if ((input.a == input.b) &&
            (input.b == input.c)){
                return 1;
        }return 0;
    } return 0;

}