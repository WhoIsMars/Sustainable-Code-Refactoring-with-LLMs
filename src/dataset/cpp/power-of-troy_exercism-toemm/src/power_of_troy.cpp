#include "power_of_troy.h"

#include <string>
#include <memory>

namespace troy {



human::human() {
    this->influenced_by = NULL;
    this->possession = NULL;
    this->own_power = NULL;
}


void give_new_artifact(human& hum, const std::string& artifact_name) {


    hum.possession = std::make_unique<artifact>(artifact_name);

}

void exchange_artifacts(std::unique_ptr<artifact>& art1, std::unique_ptr<artifact>& art2) {

    auto temp1 = std::move(art1);

    art1 = std::move(art2);
    art2 = std::move(temp1);   


}


void manifest_power(human& hum, const std::string& pwr) {

    hum.own_power = std::make_shared<power>(pwr);
}


void use_power(human& caster, human& target) {

    target.influenced_by = caster.own_power;

}

int power_intensity(human& hum) {

    return hum.own_power.use_count();

}

}  // namespace troy
