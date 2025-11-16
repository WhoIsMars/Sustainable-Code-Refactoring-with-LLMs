#include "space_age.h"

space_age::space_age::space_age(double input) : time(input) {}

double space_age::space_age::calculate(double planet) const {
	return time / (earth * planet);
}

double space_age::space_age::seconds(void) const {
	return time;
}

double space_age::space_age::on_earth(void) const {
	return time / earth;
}

double space_age::space_age::on_mercury(void) const {
	return time / (earth * mercury);
}

double space_age::space_age::on_venus(void) const {
	return time / (earth * venus);
}

double space_age::space_age::on_mars(void) const {
	return time / (earth * mars);
}

double space_age::space_age::on_jupiter(void) const {
	return time / (earth * jupiter);
}

double space_age::space_age::on_saturn(void) const {
	return time / (earth * saturn);
}

double space_age::space_age::on_uranus(void) const {
	return time / (earth * uranus);
}

double space_age::space_age::on_neptune(void) const {
	return time / (earth * neptune);
}