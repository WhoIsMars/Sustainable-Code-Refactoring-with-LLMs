#include "space_age.h"

#define EARTH_YEAR_IN_SECONDS 31557600.0f

float age(planet_t planet, int64_t seconds) {
    float earth_age = (float)seconds / EARTH_YEAR_IN_SECONDS;

    switch (planet) {
        case MERCURY:
            return earth_age / 0.2408467f;
        case VENUS:
            return earth_age / 0.61519726f;
        case EARTH:
            return earth_age;
        case MARS:
            return earth_age / 1.8808158f;
        case JUPITER:
            return earth_age / 11.862615f;
        case SATURN:
            return earth_age / 29.447498f;
        case URANUS:
            return earth_age / 84.016846f;
        case NEPTUNE:
            return earth_age / 164.79132f;
        default:
            return earth_age;
    }
}