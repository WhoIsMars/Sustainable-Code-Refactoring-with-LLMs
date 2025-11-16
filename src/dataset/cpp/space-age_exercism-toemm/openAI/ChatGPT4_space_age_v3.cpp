#include "space_age.h"

namespace space_age {

    constexpr double EARTH_ORBIT = 31557600.0;
    constexpr double MERCURY_ORBIT = EARTH_ORBIT * 0.2408467;
    constexpr double VENUS_ORBIT = EARTH_ORBIT * 0.61519726;
    constexpr double MARS_ORBIT = EARTH_ORBIT * 1.8808158;
    constexpr double JUPITER_ORBIT = EARTH_ORBIT * 11.862615;
    constexpr double SATURN_ORBIT = EARTH_ORBIT * 29.447498;
    constexpr double URANUS_ORBIT = EARTH_ORBIT * 84.016846;
    constexpr double NEPTUNE_ORBIT = EARTH_ORBIT * 164.79132;

    space_age::space_age(double seconds) : secs(seconds) {}

    double space_age::seconds() const { return secs; }

    double space_age::on_earth() const { return secs / EARTH_ORBIT; }
    double space_age::on_mercury() const { return secs / MERCURY_ORBIT; }
    double space_age::on_venus() const { return secs / VENUS_ORBIT; }
    double space_age::on_mars() const { return secs / MARS_ORBIT; }
    double space_age::on_jupiter() const { return secs / JUPITER_ORBIT; }
    double space_age::on_saturn() const { return secs / SATURN_ORBIT; }
    double space_age::on_uranus() const { return secs / URANUS_ORBIT; }
    double space_age::on_neptune() const { return secs / NEPTUNE_ORBIT; }

}  // namespace space_age