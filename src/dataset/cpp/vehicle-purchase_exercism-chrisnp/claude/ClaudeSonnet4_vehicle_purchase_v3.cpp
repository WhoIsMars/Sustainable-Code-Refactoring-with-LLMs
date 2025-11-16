#include "vehicle_purchase.h"

namespace vehicle_purchase {
    bool needs_license(const string &kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    string choose_vehicle(const string &option1, const string &option2) noexcept {
        const string& choice = (option1 < option2) ? option1 : option2;
        return choice + " is clearly the better choice.";
    }

    auto calculate_resell_price(const double& original_price, 
                                const double& age) noexcept -> double {
        const double discount = (age < 3) ? 0.8 : (age < 10) ? 0.7 : 0.5;
        return original_price * discount;
    }
}