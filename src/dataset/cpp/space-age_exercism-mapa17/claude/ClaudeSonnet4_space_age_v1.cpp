#include "space_age.h"

namespace space_age {
    space_age::space_age(uint64_t newageSec) : ageSec(newageSec), earthAge(newageSec / cx_sec2year) {
    }

    uint64_t space_age::seconds() const {
        return ageSec;
    }
    
    double space_age::on_earth() const {
        return earthAge;
    }

    double space_age::on_mercury() const {
        return earthAge / cx_earth2mercury;
    }
 
    double space_age::on_venus() const {
        return earthAge / cx_earth2venus;
    }

    double space_age::on_mars() const {
        return earthAge / cx_earth2mars;
    }
 
    double space_age::on_jupiter() const {
        return earthAge / cx_earth2jupiter;
    }
 
    double space_age::on_saturn() const {
        return earthAge / cx_earth2saturn;
    }
 
    double space_age::on_uranus() const {
        return earthAge / cx_earth2uranus;
    }
  
    double space_age::on_neptune() const {
        return earthAge / cx_earth2neptun;
    }
}  // namespace space_age