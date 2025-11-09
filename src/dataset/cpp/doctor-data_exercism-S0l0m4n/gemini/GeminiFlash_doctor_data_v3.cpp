/**
 * Doctor data exercise
 */

#include "doctor_data.h"

using heaven::Vessel;

Vessel Vessel::replicate(std::string name) {
    return {name, this->generation + 1, this->current_system};
}

void Vessel::make_buster() {
    busters++;
}

bool Vessel::shoot_buster() {
    if (busters > 0) {
        busters--;
        return true;
    }

    return false;
}

std::string heaven::get_older_bob(const Vessel& v1, const Vessel& v2) {
    return (v1.generation < v2.generation) ? v1.name : v2.name;
}

bool heaven::in_the_same_system(const Vessel& v1, const Vessel& v2) {
    return v1.current_system == v2.current_system;
}