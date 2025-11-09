#include <cassert>
#include "space_age.h"

namespace space_age {
    // private
    age_in_years space_age::age_on_planet(double earth_years_on_planet) const noexcept {
        return _earth_age_in_seconds * _inv_secs_in_earth_year / earth_years_on_planet;
    }

    // public
    space_age::space_age(age_in_seconds earth_age_in_seconds) noexcept
        : _earth_age_in_seconds(earth_age_in_seconds),
          _inv_secs_in_earth_year(1.0 / secs_in_earth_year) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const noexcept {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const noexcept {
        return age_on_planet(earth_years_on_earth);
    }

    age_in_years space_age::on_mercury() const noexcept {
        return age_on_planet(earth_years_on_mercury);
    }

    age_in_years space_age::on_venus() const noexcept {
        return age_on_planet(earth_years_on_venus);
    }

    age_in_years space_age::on_mars() const noexcept {
        return age_on_planet(earth_years_on_mars);
    }

    age_in_years space_age::on_jupiter() const noexcept {
        return age_on_planet(earth_years_on_jupiter);
    }

    age_in_years space_age::on_saturn() const noexcept {
        return age_on_planet(earth_years_on_saturn);
    }

    age_in_years space_age::on_uranus() const noexcept {
        return age_on_planet(earth_years_on_uranus);
    }

    age_in_years space_age::on_neptune() const noexcept {
        return age_on_planet(earth_years_on_neptune);
    }
}  // namespace space_age