#include "vehicle_purchase.h"

namespace vehicle_purchase {
    // needs_license determines whether a license is needed to drive a type of vehicle. 
    // Only "car" and "truck" require a license.
    bool needs_license(const string &kind) noexcept {
        return (kind == "car" || kind == "truck");
    }
    // choose_vehicle recommends a vehicle for selection. It always recommends the vehicle 
    // that comes first in lexicographical order.
    string choose_vehicle(const string &option1, const string &option2) noexcept {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }
    // calculate_resell_price calculates how much a vehicle can resell for at a certain age.
    double calculate_resell_price(const double& original_price, const double& age) noexcept {
        const double discount = (age < 3) ? 0.8 : (age < 10) ? 0.7 : 0.5;
        return original_price * discount;
    }

}  // namespace vehicle_purchase