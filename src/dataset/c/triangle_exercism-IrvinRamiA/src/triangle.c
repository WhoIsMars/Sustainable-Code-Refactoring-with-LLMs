#include "triangle.h"

static bool complies_triangle_inequality(triangle_t triangle)
{
    bool result = false;

    if (triangle.a + triangle.b > triangle.c &&
        triangle.b + triangle.c > triangle.a &&
        triangle.c + triangle.a > triangle.b)
    {
        result = true;
    }

    return result;
}

bool is_equilateral(triangle_t triangle)
{
    bool result = false;

    if (triangle.a == triangle.b && triangle.b == triangle.c)
    {
        if (triangle.a == 0)
        {
            result = false;
        }
        else
        {
            result = true;
        }
    }

    return result;
}

bool is_isosceles(triangle_t triangle)
{
    bool result = false;

    if ((is_equilateral(triangle) ||
         !is_scalene(triangle)) &&
        complies_triangle_inequality(triangle))
    {
        result = true;
    }
    return result;
}

bool is_scalene(triangle_t triangle)
{
    bool result = false;

    if (triangle.a != triangle.b &&
        triangle.b != triangle.c &&
        triangle.c != triangle.a &&
        complies_triangle_inequality(triangle))
    {
        result = true;
    }

    return result;
}
