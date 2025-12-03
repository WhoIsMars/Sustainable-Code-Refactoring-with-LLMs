#include "space_age.h"

static const float ORBITAL_PERIOD_MULTIPLIERS[] = {
    [MERCURY] = 1.0f / 0.2408467f,
    [VENUS] = 1.0f / 0.61519726f,
    [EARTH] = 1.0f,
    [MARS] = 1.0f / 1.8808158f,
    [JUPITER] = 1.0f / 11.862615f,
    [SATURN] = 1.0f / 29.447498f,
    [URANUS] = 1.0f / 84.016846f,
    [NEPTUNE] = 1.0f / 164.79132f
};

static const float SECONDS_PER_EARTH_YEAR = 31557600.0f;

static float seconds_to_earth_years(int64_t seconds);

float age(planet_t planet, int64_t seconds)
{
    if (planet < MERCURY || planet > NEPTUNE) {
        return -1.0f;
    }
    
    return seconds_to_earth_years(seconds) * ORBITAL_PERIOD_MULTIPLIERS[planet];
}

static float seconds_to_earth_years(int64_t seconds)
{
    return (float)seconds / SECONDS_PER_EARTH_YEAR;
}