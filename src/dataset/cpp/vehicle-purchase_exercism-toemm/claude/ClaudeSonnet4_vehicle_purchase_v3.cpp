#include "vehicle_purchase.h"

namespace vehicle_purchase {

bool needs_license(const std::string& kind) {
    return kind == "car" || kind == "truck";
}

std::string choose_vehicle(const std::string& option1, const std::string& option2) {
    if (option1 < option2) {
        return option1 + " is clearly the better choice.";
    }
    return option2 + " is clearly the better choice.";
}

double calculate_resell_price(double original_price, double age) {
    if (age < 3) {
        return original_price * 0.8;
    }
    if (age < 10) {
        return original_price * 0.7;
    }
    return original_price * 0.5;
}

}  // namespace vehicle_purchase