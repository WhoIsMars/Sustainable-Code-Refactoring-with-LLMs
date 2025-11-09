#include <cassert>
#include "space_age.h"

namespace space_age {
    // Precompute reciprocals to avoid division in runtime
    static constexpr double earth_years_reciprocal = 1.0 / earth_years_on_earth;
    static constexpr double mercury_years_reciprocal = 1.0 / earth_years_on_mercury;
    static constexpr double venus_years_reciprocal = 1.0 / earth_years_on_venus;
    static constexpr double mars_years_reciprocal = 1.0 / earth_years_on_mars;
    static constexpr double jupiter_years_reciprocal = 1.0 / earth_years_on_jupiter;
    static constexpr double saturn_years_reciprocal = 1.0 / earth_years_on_saturn;
    static constexpr double uranus_years_reciprocal = 1.0 / earth_years_on_uranus;
    static constexpr double neptune_years_reciprocal = 1.0 / earth_years_on_neptune;
    
    static constexpr double secs_in_earth_year_reciprocal = 1.0 / secs_in_earth_year;

    // public
    space_age::space_age(age_in_seconds earth_age_in_seconds) 
        : _earth_age_in_seconds(earth_age_in_seconds) {
        assert(earth_age_in_seconds >= 0);
    }

    age_in_seconds space_age::seconds() const {
        return _earth_age_in_seconds;
    }

    age_in_years space_age::on_earth() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * earth_years_reciprocal;
    }

    age_in_years space_age::on_mercury() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * mercury_years_reciprocal;
    }

    age_in_years space_age::on_venus() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * venus_years_reciprocal;
    }

    age_in_years space_age::on_mars() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * mars_years_reciprocal;
    }

    age_in_years space_age::on_jupiter() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * jupiter_years_reciprocal;
    }

    age_in_years space_age::on_saturn() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * saturn_years_reciprocal;
    }

    age_in_years space_age::on_uranus() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * uranus_years_reciprocal;
    }

    age_in_years space_age::on_neptune() const {
        return _earth_age_in_seconds * secs_in_earth_year_reciprocal * neptune_years_reciprocal;
    }
}  // namespace space_age