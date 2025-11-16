#include "power_of_troy.h"

#include <string>
#include <memory>

namespace troy {

H::human() noexcept {
    this->influenced_by = nullptr;
    this->possession = nullptr;
    this->own_power = nullptr;
}

void give_new_artifact(human& hum, const std::string& artifact_name) {
    hum.possession = std::make_unique<artifact>(artifact_name);
}

void exchange_artifacts(std::unique_ptr<artifact>& art1, std::unique_ptr<artifact>& art2) noexcept {
    art1.swap(art2);
}

void manifest_power(human& hum, const std::string& pwr) {
    hum.own_power = std::make_shared<power>(pwr);
}

void use_power(human& caster, human& target) noexcept {
    target.influenced_by = caster.own_power;
}

int power_intensity(human& hum) noexcept {
    return hum.own_power.use_count();
}

}  // namespace troy