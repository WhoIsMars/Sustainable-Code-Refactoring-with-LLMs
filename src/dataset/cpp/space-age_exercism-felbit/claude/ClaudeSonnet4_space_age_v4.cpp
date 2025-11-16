#include "space_age.h"

namespace space_age {
    constexpr double SECONDS_PER_EARTH_YEAR = 31557600.0;
    constexpr double MERCURY_YEARS = 0.2408467;
    constexpr double VENUS_YEARS = 0.61519726;
    constexpr double MARS_YEARS = 1.8808158;
    constexpr double JUPITER_YEARS = 11.862615;
    constexpr double SATURN_YEARS = 29.447498;
    constexpr double URANUS_YEARS = 84.016846;
    constexpr double NEPTUNE_YEARS = 164.79132;

    space_age::space_age(unsigned long long int seconds) : m_seconds(seconds), m_earth_years(seconds / SECONDS_PER_EARTH_YEAR) {}

    unsigned long long int space_age::seconds() const
    {
        return m_seconds;
    }

    double space_age::on_earth() const
    {
        return m_earth_years;
    }

    double space_age::per_earth_years(double planet_years) const
    {
        return m_earth_years / planet_years;
    }

    double space_age::on_mercury() const
    {
        return m_earth_years / MERCURY_YEARS;
    }

    double space_age::on_venus() const
    {
        return m_earth_years / VENUS_YEARS;
    }
    
    double space_age::on_mars() const
    {
        return m_earth_years / MARS_YEARS;
    }

    double space_age::on_jupiter() const
    {
        return m_earth_years / JUPITER_YEARS;
    }

    double space_age::on_saturn() const
    {
        return m_earth_years / SATURN_YEARS;
    }

    double space_age::on_uranus() const
    {
        return m_earth_years / URANUS_YEARS;
    }

    double space_age::on_neptune() const
    {
        return m_earth_years / NEPTUNE_YEARS;
    }
}