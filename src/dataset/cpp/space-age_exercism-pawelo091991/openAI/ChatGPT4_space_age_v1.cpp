#include "space_age.h"

namespace space_age {

space_age::space_age(double input) : time(input) {}

double space_age::calculate(double planet) const {
	static constexpr double earth_year_in_seconds = 31557600.0;
	return time / (earth_year_in_seconds * planet);
}

double space_age::seconds() const {
	return time;
}

double space_age::on_earth() const {
	return calculate(1.0);
}

double space_age::on_mercury() const {
	static constexpr double mercury = 0.2408467;
	return calculate(mercury);
}

double space_age::on_venus() const {
	static constexpr double venus = 0.61519726;
	return calculate(venus);
}

double space_age::on_mars() const {
	static constexpr double mars = 1.8808158;
	return calculate(mars);
}

double space_age::on_jupiter() const {
	static constexpr double jupiter = 11.862615;
	return calculate(jupiter);
}

double space_age::on_saturn() const {
	static constexpr double saturn = 29.447498;
	return calculate(saturn);
}

double space_age::on_uranus() const {
	static constexpr double uranus = 84.016846;
	return calculate(uranus);
}

double space_age::on_neptune() const {
	static constexpr double neptune = 164.79132;
	return calculate(neptune);
}

} // namespace space_age