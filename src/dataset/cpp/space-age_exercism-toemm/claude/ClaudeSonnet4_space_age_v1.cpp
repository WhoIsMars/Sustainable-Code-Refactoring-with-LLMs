#include "space_age.h"

namespace space_age {

    space_age::space_age(double seconds): secs(seconds) {}
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