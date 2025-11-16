#include "vehicle_purchase.h"
#include <string_view>

namespace vehicle_purchase {

    bool needs_license(std::string_view kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string& option1, const std::string& option2) {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }

    double calculate_resell_price(double original_price, double age) noexcept {
        return original_price * (age < 3 ? 0.80 : (age < 10 ? 0.70 : 0.50));
    }

}  // namespace vehicle_purchase