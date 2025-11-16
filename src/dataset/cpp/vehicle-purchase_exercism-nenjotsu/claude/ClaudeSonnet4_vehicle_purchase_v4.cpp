#include "vehicle_purchase.h"

namespace vehicle_purchase {

    bool needs_license(const std::string& kind) noexcept {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string& option1, const std::string& option2) {
        constexpr const char* suffix = " is clearly the better choice.";
        if (option1 < option2) {
            std::string result;
            result.reserve(option1.size() + 32);
            result = option1;
            result += suffix;
            return result;
        }
        std::string result;
        result.reserve(option2.size() + 32);
        result = option2;
        result += suffix;
        return result;
    }

    double calculate_resell_price(double original_price, double age) noexcept {
        if (age < 3.0) {
            return original_price * 0.8;
        } else if (age < 10.0) {
            return original_price * 0.7;
        } else {
            return original_price * 0.5;
        }
    }

}