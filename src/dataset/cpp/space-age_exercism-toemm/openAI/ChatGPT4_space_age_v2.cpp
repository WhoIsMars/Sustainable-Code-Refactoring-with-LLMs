#include "space_age.h"

namespace space_age {

    space_age::space_age(double seconds): secs(seconds), earth_years(seconds / EARTH_ORBIT) {}
    
    double space_age::seconds() const { return secs; }
    double space_age::on_earth() const { return earth_years; }
    double space_age::on_mercury() const { return earth_years / MERCURY_ORBIT_RATIO; }
    double space_age::on_venus() const { return earth_years / VENUS_ORBIT_RATIO; }
    double space_age::on_mars() const { return earth_years / MARS_ORBIT_RATIO; }
    double space_age::on_jupiter() const { return earth_years / JUPITER_ORBIT_RATIO; }
    double space_age::on_saturn() const { return earth_years / SATURN_ORBIT_RATIO; }
    double space_age::on_uranus() const { return earth_years / URANUS_ORBIT_RATIO; }
    double space_age::on_neptune() const { return earth_years / NEPTUNE_ORBIT_RATIO; }

}  // namespace space_age