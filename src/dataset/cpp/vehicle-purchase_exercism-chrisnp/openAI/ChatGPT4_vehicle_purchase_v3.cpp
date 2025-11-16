#include "vehicle_purchase.h"
#include <algorithm>

namespace vehicle_purchase {

    bool needs_license(const std::string &kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string &option1, const std::string &option2) noexcept {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }

    double calculate_resell_price(double original_price, double age) noexcept {
        constexpr double discount_new = 0.8;
        constexpr double discount_mid = 0.7;
        constexpr double discount_old = 0.5;

        return original_price * (age < 3 ? discount_new : (age < 10 ? discount_mid : discount_old));
    }

}  // namespace vehicle_purchase