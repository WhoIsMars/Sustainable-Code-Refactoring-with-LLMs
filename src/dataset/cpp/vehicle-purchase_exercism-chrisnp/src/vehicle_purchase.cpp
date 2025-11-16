#include "vehicle_purchase.h"

namespace vehicle_purchase {
    // needs_license determines whether a license is needed to drive a type of vehicle. 
    // Only "car" and "truck" require a license.
    bool needs_license(const string &kind) noexcept {
        return !(!(kind == "car") && !(kind == "truck"));
    }
    // choose_vehicle recommends a vehicle for selection. It always recommends the vehicle 
    // that comes first in lexicographical order.
    string choose_vehicle(const string &option1, const string &option2) noexcept {
        return min(option1, option2) + " is clearly the better choice.";
    }
    // calculate_resell_price calculates how much a vehicle can resell for at a certain age.
    auto calculate_resell_price(const double& original_price, 
                                const double& age) noexcept -> double {
        double discount { 1.0 };
        if (age < 3) discount = 0.8;
        else if (age < 10) discount = 0.7;
        else discount = 0.5;
        return original_price * discount;
    }

}  // namespace vehicle_purchase