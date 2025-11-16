#include "space_age.h"

namespace space_age {
	space_age::space_age(double age_in_seconds) : age(age_in_seconds) {}

	int space_age::seconds() const {
		return static_cast<int>(age);
	}

	double space_age::on_earth() const {
		return age / earth_seconds;
	}

	double space_age::on_mercury() const {
		return age / (earth_seconds * mercury_ratio);
	}

	double space_age::on_venus() const {
		return age / (earth_seconds * venus_ratio);
	}

	double space_age::on_mars() const {
		return age / (earth_seconds * mars_ratio);
	}

	double space_age::on_jupiter() const {
		return age / (earth_seconds * jupiter_ratio);
	}

	double space_age::on_saturn() const {
		return age / (earth_seconds * saturn_ratio);
	}

	double space_age::on_uranus() const {
		return age / (earth_seconds * uranus_ratio);
	}

	double space_age::on_neptune() const {
		return age / (earth_seconds * neptune_ratio);
	}
}  // namespace space_age