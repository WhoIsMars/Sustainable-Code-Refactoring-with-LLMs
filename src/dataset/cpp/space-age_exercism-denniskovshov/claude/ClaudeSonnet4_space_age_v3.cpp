#include <cassert>
#include "space_age.h"

namespace space_age {
    constexpr double inv_secs_in_earth_year = 1.0 / secs_in_earth_year;
    constexpr double inv_earth_years_on_earth = 1.0 / earth_years_on_earth;
    constexpr double inv_earth_years_on_mercury = 1.0 / earth_years_on_mercury;
    constexpr double inv_earth_years_on_venus = 1.0 / earth_years_on_venus;
    constexpr double inv_earth_years_on_mars = 1.0 / earth_years_on_mars;
    constexpr double inv_earth_years_on_jupiter = 1.0 / earth_years_on_jupiter;
    constexpr double inv_earth_years_on_saturn = 1.0 / earth_years_on_saturn;
    constexpr double inv_earth_years_on_uranus = 1.0 / earth_years_on_uranus;
    constexpr double inv_earth_years_on_neptune = 1.0 / earth_years_on_neptune;

    space_age::space_age(age_in_seconds earth_age_in_seconds) noexcept
        : _earth_age_in_seconds(earth_age_in_seconds) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const noexcept {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_earth;
    }

    age_in_years space_age::on_mercury() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_mercury;
    }

    age_in_years space_age::on_venus() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_venus;
    }

    age_in_years space_age::on_mars() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_mars;
    }

    age_in_years space_age::on_jupiter() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_jupiter;
    }

    age_in_years space_age::on_saturn() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_saturn;
    }

    age_in_years space_age::on_uranus() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_uranus;
    }

    age_in_years space_age::on_neptune() const noexcept {
        return _earth_age_in_seconds * inv_secs_in_earth_year * inv_earth_years_on_neptune;
    }
}