#include "doctor_data.h"

heaven::Vessel::Vessel(const std::string& name, int i, const star_map::System& sys)
    : name(name), generation(i), current_system(sys), busters(0) {}

heaven::Vessel heaven::Vessel::replicate(const std::string& newname) {
    return Vessel(newname, this->generation + 1, star_map::System::Sol);
}

void heaven::Vessel::make_buster() {
    ++this->busters;
}

bool heaven::Vessel::shoot_buster() {
    if (this->busters > 0) {
        --this->busters;
        return true;
    }
    return false;
}

std::string heaven::get_older_bob(const Vessel& v1, const Vessel& v2) {
    return (v1.generation <= v2.generation) ? v1.name : v2.name;
}

bool heaven::in_the_same_system(const Vessel& v1, const Vessel& v2) {
    return v1.current_system == v2.current_system;
}