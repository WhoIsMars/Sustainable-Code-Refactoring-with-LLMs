#include "space_age.h"

#define EARTH_YEAR_SECONDS 31557600.0f

float age(planet_t planet, int64_t seconds) {
    float result = seconds / EARTH_YEAR_SECONDS;

    switch (planet) {
        case MERCURY:
            result /= 0.2408467f;
            break;
        case VENUS:
            result /= 0.61519726f;
            break;
        case MARS:
            result /= 1.8808158f;
            break;
        case JUPITER:
            result /= 11.862615f;
            break;
        case SATURN:
            result /= 29.447498f;
            break;
        case URANUS:
            result /= 84.016846f;
            break;
        case NEPTUNE:
            result /= 164.79132f;
            break;
        default:
            break;
    }

    return result;
}