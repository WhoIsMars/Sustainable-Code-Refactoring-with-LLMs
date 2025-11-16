#include "space_age.h"

namespace space_age {

    constexpr double seconds_per_earth_year = 31557600.0;
    constexpr double inv_seconds_per_earth_year = 1.0 / seconds_per_earth_year;

    constexpr double inv_orbital_period_mercury = 1.0 / 0.2408467;
    constexpr double inv_orbital_period_venus   = 1.0 / 0.61519726;
    constexpr double inv_orbital_period_mars    = 1.0 / 1.8808158;
    constexpr double inv_orbital_period_jupiter = 1.0 / 11.862615;
    constexpr double inv_orbital_period_saturn  = 1.0 / 29.447498;
    constexpr double inv_orbital_period_uranus  = 1.0 / 84.016846;
    constexpr double inv_orbital_period_neptune = 1.0 / 164.79132;

    space_age::space_age(std::uint64_t earth_age_in_seconds) 
        : _earth_age_in_seconds(earth_age_in_seconds) {}

    std::uint64_t space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    double space_age::on_earth() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year;
    }

    double space_age::on_mercury() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_mercury;
    }

    double space_age::on_venus() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_venus;
    }

    double space_age::on_mars() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_mars;
    }

    double space_age::on_jupiter() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_jupiter;
    }

    double space_age::on_saturn() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_saturn;
    }

    double space_age::on_uranus() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_uranus;
    }

    double space_age::on_neptune() const {
        return _earth_age_in_seconds * inv_seconds_per_earth_year * inv_orbital_period_neptune;
    }

}