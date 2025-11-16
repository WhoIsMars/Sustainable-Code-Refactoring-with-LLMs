#include "space_age.h"

space_age::space_age::space_age(double input) noexcept : time(input) {}

double space_age::space_age::calculate(double planet) const noexcept {
	return time / (earth * planet);
}

double space_age::space_age::seconds() const noexcept {
	return time;
}

double space_age::space_age::on_earth() const noexcept {
	return time / earth;
}

double space_age::space_age::on_mercury() const noexcept {
	return time / (earth * mercury);
}

double space_age::space_age::on_venus() const noexcept {
	return time / (earth * venus);
}

double space_age::space_age::on_mars() const noexcept {
	return time / (earth * mars);
}

double space_age::space_age::on_jupiter() const noexcept {
	return time / (earth * jupiter);
}

double space_age::space_age::on_saturn() const noexcept {
	return time / (earth * saturn);
}

double space_age::space_age::on_uranus() const noexcept {
	return time / (earth * uranus);
}

double space_age::space_age::on_neptune() const noexcept {
	return time / (earth * neptune);
}