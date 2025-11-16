#include "space_age.h"

static constexpr double Orbital_Period_Seconds[] {
    0.2408467 * 31557600.0, 0.61519726 * 31557600.0, 1.0000000 * 31557600.0, 1.8808158 * 31557600.0, 
    11.862615 * 31557600.0, 29.447498 * 31557600.0, 84.016846 * 31557600.0, 164.79132 * 31557600.0
};

space_age::space_age::space_age(const uint_fast64_t _seconds): age(_seconds) {}

uint_fast64_t space_age::space_age::seconds() const noexcept {
    return age;
}

float space_age::space_age::on_mercury() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[0]);
}
float space_age::space_age::on_venus() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[1]);
}
float space_age::space_age::on_earth() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[2]);
}
float space_age::space_age::on_mars() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[3]);
}
float space_age::space_age::on_jupiter() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[4]);
}
float space_age::space_age::on_saturn() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[5]);
}
float space_age::space_age::on_uranus() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[6]);
}
float space_age::space_age::on_neptune() const noexcept { 
    return static_cast<float>(age / Orbital_Period_Seconds[7]);
}