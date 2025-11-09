#include <cassert>
#include "space_age.h"

namespace space_age {

    // Constants for planet orbital periods relative to Earth.
    constexpr double earth_years_on_mercury_val = 0.2408467;
    constexpr double earth_years_on_venus_val = 0.61519726;
    constexpr double earth_years_on_mars_val = 1.8808158;
    constexpr double earth_years_on_jupiter_val = 11.862615;
    constexpr double earth_years_on_saturn_val = 29.447498;
    constexpr double earth_years_on_uranus_val = 84.016846;
    constexpr double earth_years_on_neptune_val = 164.79132;

    space_age::space_age(age_in_seconds earth_age_in_seconds) : _earth_age_in_seconds(earth_age_in_seconds) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year);
    }

    age_in_years space_age::on_mercury() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_mercury_val);
    }

    age_in_years space_age::on_venus() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_venus_val);
    }

    age_in_years space_age::on_mars() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_mars_val);
    }

    age_in_years space_age::on_jupiter() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_jupiter_val);
    }

    age_in_years space_age::on_saturn() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_saturn_val);
    }

    age_in_years space_age::on_uranus() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_uranus_val);
    }

    age_in_years space_age::on_neptune() const {
        return static_cast<age_in_years>(_earth_age_in_seconds / secs_in_earth_year / earth_years_on_neptune_val);
    }
}  // namespace space_age