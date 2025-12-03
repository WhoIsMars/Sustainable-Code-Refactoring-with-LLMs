#include "space_age.h"

static float seconds_to_earth_years(int64_t seconds);

float age(planet_t planet, int64_t seconds)
{
    switch (planet)
    {
    case MERCURY:
        return seconds_to_earth_years(seconds) / 0.2408467;
    case VENUS:
        return seconds_to_earth_years(seconds) / 0.61519726;
    case EARTH:
        return seconds_to_earth_years(seconds);
    case MARS:
        return seconds_to_earth_years(seconds) / 1.8808158;
    case JUPITER:
        return seconds_to_earth_years(seconds) / 11.862615;
    case SATURN:
        return seconds_to_earth_years(seconds) / 29.447498;
    case URANUS:
        return seconds_to_earth_years(seconds) / 84.016846;
    case NEPTUNE:
        return seconds_to_earth_years(seconds) / 164.79132;
    default:
        return -1;
        break;
    }

}
static float seconds_to_earth_years(int64_t seconds)
{
    // 1 minute = 60 seconds
    // 1 hour = 60 minutes
    // 1 day = 24 hours
    // 1 year = 365,25 days
    const float seconds_per_year = 60 * 60 * 24 * 365.25;
    return seconds / seconds_per_year;
}