#include <cassert>
#include "space_age.h"

namespace space_age {
    // private
    constexpr double SECONDS_IN_EARTH_YEAR = 31557600.0;

    age_in_years space_age::age_on_planet(double orbital_ratio) const {
        return _earth_age_in_seconds / (SECONDS_IN_EARTH_YEAR * orbital_ratio);
    }

    // public
    space_age::space_age(age_in_seconds earth_age_in_seconds) : _earth_age_in_seconds(earth_age_in_seconds) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const {
        return age_on_planet(1.0);
    }

    age_in_years space_age::on_mercury() const {
        return age_on_planet(0.2408467);
    }

    age_in_years space_age::on_venus() const {
        return age_on_planet(0.61519726);
    }

    age_in_years space_age::on_mars() const {
        return age_on_planet(1.8808158);
    }

    age_in_years space_age::on_jupiter() const {
        return age_on_planet(11.862615);
    }

    age_in_years space_age::on_saturn() const {
        return age_on_planet(29.447498);
    }

    age_in_years space_age::on_uranus() const {
        return age_on_planet(84.016846);
    }

    age_in_years space_age::on_neptune() const {
        return age_on_planet(164.79132);
    }
}  // namespace space_age