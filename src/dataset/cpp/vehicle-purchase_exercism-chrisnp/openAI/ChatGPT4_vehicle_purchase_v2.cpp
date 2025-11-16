#include "vehicle_purchase.h"
#include <algorithm>

namespace vehicle_purchase {
    // needs_license determines whether a license is needed to drive a type of vehicle. 
    // Only "car" and "truck" require a license.
    inline bool needs_license(const string &kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    // choose_vehicle recommends a vehicle for selection. It always recommends the vehicle 
    // that comes first in lexicographical order.
    inline string choose_vehicle(const string &option1, const string &option2) noexcept {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }

    // calculate_resell_price calculates how much a vehicle can resell for at a certain age.
    inline double calculate_resell_price(double original_price, double age) noexcept {
        constexpr double discount_under_3 = 0.8;
        constexpr double discount_under_10 = 0.7;
        constexpr double discount_over_10 = 0.5;

        double discount = (age < 3) ? discount_under_3 : (age < 10 ? discount_under_10 : discount_over_10);
        return original_price * discount;
    }

}  // namespace vehicle_purchase