#include "vehicle_purchase.h"
#include <algorithm>

namespace vehicle_purchase {

    // needs_license determines whether a license is needed to drive a type of vehicle. Only "car" and "truck" require a license.
    bool needs_license(std::string kind){
        std::transform(kind.begin(), kind.end(), kind.begin(), ::tolower);
        return (kind == "car" || kind == "truck");
    }

    // choose_vehicle recommends a vehicle for selection. It always recommends the vehicle that comes first in lexicographical order.
    std::string choose_vehicle(std::string option1, std::string option2) {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }

    // calculate_resell_price calculates how much a vehicle can resell for at a certain age.
    double calculate_resell_price(double original_price, double age) {
        double resell_percentage;
        if (age < 3) {
            resell_percentage = 0.80;
        } else if (age < 10) {
            resell_percentage = 0.70;
        } else {
            resell_percentage = 0.50;
        }
        return original_price * resell_percentage;
    }

}  // namespace vehicle_purchase