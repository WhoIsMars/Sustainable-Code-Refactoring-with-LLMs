#include "space_age.h"

namespace space_age {

    
    space_age::space_age(double seconds): secs(seconds) {}
    double space_age::seconds() const { return this->secs; }
    double space_age::on_earth() const { return this->seconds() / EARTH_ORBIT; }
    double space_age::on_mercury() const { return this->seconds() / MERCURY_ORBIT; }
    double space_age::on_venus() const { return this->seconds() / VENUS_ORBIT; }
    double space_age::on_mars() const { return this->seconds() / MARS_ORBIT; }
    double space_age::on_jupiter() const { return this->seconds() / JUPITER_ORBIT; }
    double space_age::on_saturn() const { return this->seconds() / SATURN_ORBIT; }
    double space_age::on_uranus() const { return this->seconds() / URANUS_ORBIT; }
    double space_age::on_neptune() const { return this->seconds() / NEPTUNE_ORBIT; }



}  // namespace space_age
