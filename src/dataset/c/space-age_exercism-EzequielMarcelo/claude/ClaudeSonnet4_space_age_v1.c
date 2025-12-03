#include "space_age.h"

static const float SECONDS_PER_EARTH_YEAR = 31557600.0f; // 60 * 60 * 24 * 365.25

static const float PLANET_MULTIPLIERS[] = {
    [MERCURY] = 1.0f / 0.2408467f,
    [VENUS] = 1.0f / 0.61519726f,
    [EARTH] = 1.0f,
    [MARS] = 1.0f / 1.8808158f,
    [JUPITER] = 1.0f / 11.862615f,
    [SATURN] = 1.0f / 29.447498f,
    [URANUS] = 1.0f / 84.016846f,
    [NEPTUNE] = 1.0f / 164.79132f
};

static inline float seconds_to_earth_years(int64_t seconds)
{
    return seconds / SECONDS_PER_EARTH_YEAR;
}

float age(planet_t planet, int64_t seconds)
{
    if (planet < 0 || planet >= sizeof(PLANET_MULTIPLIERS) / sizeof(PLANET_MULTIPLIERS[0])) {
        return -1;
    }
    
    return seconds_to_earth_years(seconds) * PLANET_MULTIPLIERS[planet];
}