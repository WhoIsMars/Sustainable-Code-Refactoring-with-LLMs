#include "space_age.h"

namespace space_age {

    space_age::space_age(double seconds): secs(seconds), 
        earth_age(seconds / EARTH_ORBIT),
        mercury_age(seconds / MERCURY_ORBIT),
        venus_age(seconds / VENUS_ORBIT),
        mars_age(seconds / MARS_ORBIT),
        jupiter_age(seconds / JUPITER_ORBIT),
        saturn_age(seconds / SATURN_ORBIT),
        uranus_age(seconds / URANUS_ORBIT),
        neptune_age(seconds / NEPTUNE_ORBIT) {}

    double space_age::seconds() const { return secs; }
    double space_age::on_earth() const { return earth_age; }
    double space_age::on_mercury() const { return mercury_age; }
    double space_age::on_venus() const { return venus_age; }
    double space_age::on_mars() const { return mars_age; }
    double space_age::on_jupiter() const { return jupiter_age; }
    double space_age::on_saturn() const { return saturn_age; }
    double space_age::on_uranus() const { return uranus_age; }
    double space_age::on_neptune() const { return neptune_age; }

}  // namespace space_age