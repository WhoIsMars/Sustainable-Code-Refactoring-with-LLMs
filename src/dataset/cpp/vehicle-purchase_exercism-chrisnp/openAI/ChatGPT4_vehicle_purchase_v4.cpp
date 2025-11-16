#include "vehicle_purchase.h"
#include <string>
#include <algorithm>

namespace vehicle_purchase {

    bool needs_license(const std::string &kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string &option1, const std::string &option2) noexcept {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }

    double calculate_resell_price(double original_price, double age) noexcept {
        return original_price * (age < 3 ? 0.8 : (age < 10 ? 0.7 : 0.5));
    }

}  // namespace vehicle_purchase