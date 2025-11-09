#include <cassert>
#include "space_age.h"

namespace space_age {
    // public
    space_age::space_age(age_in_seconds earth_age_in_seconds) 
        : _earth_age_in_seconds(earth_age_in_seconds),
          _earth_age_in_years(earth_age_in_seconds / secs_in_earth_year) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const {
        return _earth_age_in_years;
    }

    age_in_years space_age::on_mercury() const {
        return _earth_age_in_years / earth_years_on_mercury;
    }

    age_in_years space_age::on_venus() const {
        return _earth_age_in_years / earth_years_on_venus;
    }

    age_in_years space_age::on_mars() const {
        return _earth_age_in_years / earth_years_on_mars;
    }

    age_in_years space_age::on_jupiter() const {
        return _earth_age_in_years / earth_years_on_jupiter;
    }

    age_in_years space_age::on_saturn() const {
        return _earth_age_in_years / earth_years_on_saturn;
    }

    age_in_years space_age::on_uranus() const {
        return _earth_age_in_years / earth_years_on_uranus;
    }

    age_in_years space_age::on_neptune() const {
        return _earth_age_in_years / earth_years_on_neptune;
    }
}  // namespace space_age