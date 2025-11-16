#include "doctor_data.h"

heaven::Vessel::Vessel(std::string name, int i, star_map::System sys){
    this->name = name;
    this->generation= i;
    this->current_system = sys;
    this->busters = 0;
}

heaven::Vessel heaven::Vessel::replicate(std::string newname) {
    Vessel new_vessel {newname, this->generation+1, star_map::System::Sol};
    
    return new_vessel;
}

void heaven::Vessel::make_buster() {
    this->busters += 1;
}

bool heaven::Vessel::shoot_buster() {
    if (this->busters) {
        this->busters--;
        return true;
    }
    else return false;
}

std::string heaven::get_older_bob(const Vessel& v1, const Vessel& v2) {
    if (v1.generation <= v2.generation) {
        return v1.name;
    } else return v2.name;

}
bool heaven::in_the_same_system(Vessel& v1, Vessel& v2) {
    if (v1.current_system == v2.current_system) return true;
    else return false;
}

