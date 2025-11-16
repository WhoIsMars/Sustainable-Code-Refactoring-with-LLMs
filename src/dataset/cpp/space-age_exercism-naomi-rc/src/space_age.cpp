#include "space_age.h"

namespace space_age {
	space_age::space_age(double age_in_seconds) {
		age = age_in_seconds;
	}

	int space_age::seconds() const {
		return age;
	}

	double space_age::on_earth() const {
		return age / earth_seconds;
	}

	double space_age::on_mercury() const {
		return this->on_earth() / mercury_ratio;
	}

	double space_age::on_venus() const {
		return this->on_earth() / venus_ratio;
	}

	double space_age::on_mars() const {
		return this->on_earth() / mars_ratio;
	}

	double space_age::on_jupiter() const {
		return this->on_earth() / jupiter_ratio;
	}

	double space_age::on_saturn() const {
		return this->on_earth() / saturn_ratio;
	}

	double space_age::on_uranus() const {
		return this->on_earth() / uranus_ratio;
	}

	double space_age::on_neptune() const {
		return this->on_earth() / neptune_ratio;
	}
}  // namespace space_age
