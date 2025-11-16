#include "space_age.h"

namespace space_age {
	space_age::space_age(double age_in_seconds) 
		: age(age_in_seconds), earth_years(age_in_seconds / earth_seconds) {}

	int space_age::seconds() const {
		return age;
	}

	double space_age::on_earth() const {
		return earth_years;
	}

	double space_age::on_mercury() const {
		return earth_years / mercury_ratio;
	}

	double space_age::on_venus() const {
		return earth_years / venus_ratio;
	}

	double space_age::on_mars() const {
		return earth_years / mars_ratio;
	}

	double space_age::on_jupiter() const {
		return earth_years / jupiter_ratio;
	}

	double space_age::on_saturn() const {
		return earth_years / saturn_ratio;
	}

	double space_age::on_uranus() const {
		return earth_years / uranus_ratio;
	}

	double space_age::on_neptune() const {
		return earth_years / neptune_ratio;
	}
}  // namespace space_age