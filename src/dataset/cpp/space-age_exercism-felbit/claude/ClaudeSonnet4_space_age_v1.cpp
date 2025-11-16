#include "space_age.h"

namespace space_age {
    static constexpr double SECONDS_PER_EARTH_YEAR = 31557600.0;
    static constexpr double MERCURY_YEARS = 0.2408467;
    static constexpr double VENUS_YEARS = 0.61519726;
    static constexpr double MARS_YEARS = 1.8808158;
    static constexpr double JUPITER_YEARS = 11.862615;
    static constexpr double SATURN_YEARS = 29.447498;
    static constexpr double URANUS_YEARS = 84.016846;
    static constexpr double NEPTUNE_YEARS = 164.79132;

    space_age::space_age(unsigned long long int seconds) : m_seconds(seconds) {}

    unsigned long long int space_age::seconds() const
    {
        return m_seconds;
    }

    double space_age::on_earth() const
    {
        return m_seconds / SECONDS_PER_EARTH_YEAR;
    }

    double space_age::per_earth_years(double planet_years) const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * planet_years);
    }

    double space_age::on_mercury() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * MERCURY_YEARS);
    }

    double space_age::on_venus() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * VENUS_YEARS);
    }
    
    double space_age::on_mars() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * MARS_YEARS);
    }

    double space_age::on_jupiter() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * JUPITER_YEARS);
    }

    double space_age::on_saturn() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * SATURN_YEARS);
    }

    double space_age::on_uranus() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * URANUS_YEARS);
    }

    double space_age::on_neptune() const
    {
        return m_seconds / (SECONDS_PER_EARTH_YEAR * NEPTUNE_YEARS);
    }
}