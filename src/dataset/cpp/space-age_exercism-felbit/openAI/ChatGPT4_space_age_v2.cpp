#include "space_age.h"

namespace space_age {
    constexpr double EARTH_YEAR_SECONDS = 31557600.0;
    constexpr double MERCURY_YEAR_RATIO = 0.2408467;
    constexpr double VENUS_YEAR_RATIO = 0.61519726;
    constexpr double MARS_YEAR_RATIO = 1.8808158;
    constexpr double JUPITER_YEAR_RATIO = 11.862615;
    constexpr double SATURN_YEAR_RATIO = 29.447498;
    constexpr double URANUS_YEAR_RATIO = 84.016846;
    constexpr double NEPTUNE_YEAR_RATIO = 164.79132;

    space_age::space_age(unsigned long long int seconds) : m_seconds(seconds), m_earth_years(seconds / EARTH_YEAR_SECONDS) {}

    unsigned long long int space_age::seconds() const
    {
        return m_seconds;
    }

    double space_age::on_earth() const
    {
        return m_earth_years;
    }

    double space_age::on_mercury() const
    {
        return m_earth_years / MERCURY_YEAR_RATIO;
    }

    double space_age::on_venus() const
    {
        return m_earth_years / VENUS_YEAR_RATIO;
    }
    
    double space_age::on_mars() const
    {
        return m_earth_years / MARS_YEAR_RATIO;
    }

    double space_age::on_jupiter() const
    {
        return m_earth_years / JUPITER_YEAR_RATIO;
    }

    double space_age::on_saturn() const
    {
        return m_earth_years / SATURN_YEAR_RATIO;
    }

    double space_age::on_uranus() const
    {
        return m_earth_years / URANUS_YEAR_RATIO;
    }

    double space_age::on_neptune() const
    {
        return m_earth_years / NEPTUNE_YEAR_RATIO;
    }
}