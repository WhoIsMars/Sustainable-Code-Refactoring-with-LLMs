#include "space_age.h"

namespace space_age {

    space_age::space_age(double seconds) noexcept : secs(seconds) {}
    
    double space_age::seconds() const noexcept { return secs; }
    
    double space_age::on_earth() const noexcept { return secs / EARTH_ORBIT; }
    
    double space_age::on_mercury() const noexcept { return secs / MERCURY_ORBIT; }
    
    double space_age::on_venus() const noexcept { return secs / VENUS_ORBIT; }
    
    double space_age::on_mars() const noexcept { return secs / MARS_ORBIT; }
    
    double space_age::on_jupiter() const noexcept { return secs / JUPITER_ORBIT; }
    
    double space_age::on_saturn() const noexcept { return secs / SATURN_ORBIT; }
    
    double space_age::on_uranus() const noexcept { return secs / URANUS_ORBIT; }
    
    double space_age::on_neptune() const noexcept { return secs / NEPTUNE_ORBIT; }

}  // namespace space_age