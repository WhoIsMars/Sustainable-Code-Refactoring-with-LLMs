#include "space_age.h"

float age(planet_t planet, int64_t seconds)
{
    float result = seconds / 31557600;
    
    switch (planet)
    {
    case MERCURY:
        result /= 0.2408467;
        break;
    case VENUS:
        result /= 0.61519726;
        break;
    case EARTH:
        break;
    case MARS:
        result /= 1.8808158;
        break;
    case JUPITER:
        result /= 11.862615;
        break;
    case SATURN:
        result /= 29.447498;
        break;
    case URANUS:
        result /= 84.016846;
        break;
    case NEPTUNE:
        result /= 164.79132;
        break;

    default:
        break;
    }

    return result;
}
