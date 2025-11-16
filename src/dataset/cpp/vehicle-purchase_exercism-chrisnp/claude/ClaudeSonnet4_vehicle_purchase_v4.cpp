#include "vehicle_purchase.h"

namespace vehicle_purchase {
    bool needs_license(const string &kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    string choose_vehicle(const string &option1, const string &option2) noexcept {
        if (option1 <= option2) {
            return option1 + " is clearly the better choice.";
        }
        return option2 + " is clearly the better choice.";
    }

    auto calculate_resell_price(const double& original_price, 
                                const double& age) noexcept -> double {
        if (age < 3) return original_price * 0.8;
        if (age < 10) return original_price * 0.7;
        return original_price * 0.5;
    }
}