#include "doctor_data.h"

namespace heaven {

Vessel::Vessel(const std::string& name, int i, const star_map::System& sys)
    : name(name), generation(i), current_system(sys), busters(0) {}

Vessel Vessel::replicate(const std::string& newname) const {
    return Vessel(newname, generation + 1, star_map::System::Sol);
}

void Vessel::make_buster() {
    ++busters;
}

bool Vessel::shoot_buster() {
    if (busters > 0) {
        --busters;
        return true;
    }
    return false;
}

std::string get_older_bob(const Vessel& v1, const Vessel& v2) {
    return (v1.generation <= v2.generation) ? v1.name : v2.name;
}

bool in_the_same_system(const Vessel& v1, const Vessel& v2) {
    return v1.current_system == v2.current_system;
}

} // namespace heaven