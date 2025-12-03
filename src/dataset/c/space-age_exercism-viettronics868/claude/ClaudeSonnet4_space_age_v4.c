#include "space_age.h"
#include <stdint.h>

static const float PLANET_ORBITAL_PERIODS[] = {
    0.2408467f,   // MERCURY
    0.61519726f,  // VENUS
    1.0f,         // EARTH
    1.8808158f,   // MARS
    11.862615f,   // JUPITER
    29.447498f,   // SATURN
    84.016846f,   // URANUS
    164.79132f    // NEPTUNE
};

static const float SECONDS_PER_EARTH_YEAR = 31557600.0f;

float seconds_to_Earth_year(uint64_t seconds){
    return (float)seconds / SECONDS_PER_EARTH_YEAR;
}

float planet_to_Earth_year(planet_t planet){
    if (planet < 0 || planet >= sizeof(PLANET_ORBITAL_PERIODS) / sizeof(PLANET_ORBITAL_PERIODS[0])) {
        return -1.0f;
    }
    return PLANET_ORBITAL_PERIODS[planet];
}

float age(planet_t planet, uint64_t seconds){
    float orbital_period = planet_to_Earth_year(planet);
    if (orbital_period == -1.0f) return -1.0f;
    return seconds_to_Earth_year(seconds) / orbital_period;
}