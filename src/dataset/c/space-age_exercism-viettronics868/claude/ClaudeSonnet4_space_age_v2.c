#include "space_age.h"
#include <stdint.h>
#include <stdio.h>

static const float PLANET_RATIOS[] = {
    0.2408467f,   // MERCURY
    0.61519726f,  // VENUS
    1.0f,         // EARTH
    1.8808158f,   // MARS
    11.862615f,   // JUPITER
    29.447498f,   // SATURN
    84.016846f,   // URANUS
    164.79132f    // NEPTUNE
};

static const float SECONDS_TO_YEAR = 1.0f / (365.25f * 24.0f * 3600.0f);

float seconds_to_Earth_year(uint64_t seconds){
    return seconds * SECONDS_TO_YEAR;
}

float planet_to_Earth_year(planet_t planet){
    if (planet < 0 || planet >= sizeof(PLANET_RATIOS)/sizeof(PLANET_RATIOS[0])) {
        return -1.0f;
    }
    return PLANET_RATIOS[planet];
}

float age(planet_t planet, uint64_t seconds){
    if (planet < 0 || planet >= sizeof(PLANET_RATIOS)/sizeof(PLANET_RATIOS[0])) {
        return -1.0f;
    }
    return seconds * SECONDS_TO_YEAR / PLANET_RATIOS[planet];
}