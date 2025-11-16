#include "space_age.h"

space_age::space_age::space_age(double input) : time(input) {}

double space_age::space_age::calculate(double planet) const {
    return time / (earth * planet);
}

double space_age::space_age::seconds() const {
    return time;
}

double space_age::space_age::on_earth() const {
    return time / earth;
}

double space_age::space_age::on_mercury() const {
    return time / (earth * mercury);
}

double space_age::space_age::on_venus() const {
    return time / (earth * venus);
}

double space_age::space_age::on_mars() const {
    return time / (earth * mars);
}

double space_age::space_age::on_jupiter() const {
    return time / (earth * jupiter);
}

double space_age::space_age::on_saturn() const {
    return time / (earth * saturn);
}

double space_age::space_age::on_uranus() const {
    return time / (earth * uranus);
}

double space_age::space_age::on_neptune() const {
    return time / (earth * neptune);
}