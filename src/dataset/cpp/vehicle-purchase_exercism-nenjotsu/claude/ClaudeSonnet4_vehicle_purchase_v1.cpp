#include "vehicle_purchase.h"

namespace vehicle_purchase {

    // needs_license determines whether a license is needed to drive a type of vehicle. Only "car" and "truck" require a license.
    bool needs_license(const std::string& kind){
        return kind == "car" || kind == "truck";
    }

    // choose_vehicle recommends a vehicle for selection. It always recommends the vehicle that comes first in lexicographical order.
    std::string choose_vehicle(const std::string& option1, const std::string& option2) {
        static const std::string suffix = " is clearly the better choice.";
        if (option1 < option2) {
            std::string result;
            result.reserve(option1.size() + suffix.size());
            return option1 + suffix;
        }
        std::string result;
        result.reserve(option2.size() + suffix.size());
        return option2 + suffix;
    }

    // calculate_resell_price calculates how much a vehicle can resell for at a certain age.
    double calculate_resell_price(double original_price, double age) {
        if (age < 3.0) {
            return original_price * 0.8;
        } else if (age < 10.0) {
            return original_price * 0.7;
        } else {
            return original_price * 0.5;
        }
    }

}  // namespace vehicle_purchase