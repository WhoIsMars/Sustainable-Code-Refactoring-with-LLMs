#include "space_age.h"
#include <stdint.h>

static const double EARTH_YEAR_IN_SECONDS = 31557600.0;

double age(planet_t planet, uint64_t seconds) {
    double orbital_period;

    switch (planet) {
        case MERCURY: orbital_period = 0.2408467; break;
        case VENUS:   orbital_period = 0.61519726; break;
        case EARTH:   orbital_period = 1.0; break;
        case MARS:    orbital_period = 1.8808158; break;
        case JUPITER: orbital_period = 11.862615; break;
        case SATURN:  orbital_period = 29.447498; break;
        case URANUS:  orbital_period = 84.016846; break;
        case NEPTUNE: orbital_period = 164.79132; break;
        default:      return -1.0;
    }

    return seconds / (EARTH_YEAR_IN_SECONDS * orbital_period);
}