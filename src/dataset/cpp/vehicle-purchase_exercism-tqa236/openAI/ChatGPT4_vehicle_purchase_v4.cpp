#include "vehicle_purchase.h"

namespace vehicle_purchase
{

    bool needs_license(const std::string& kind)
    {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string& option1, const std::string& option2)
    {
        return (option1 < option2 ? option1 : option2) + " is clearly the better choice.";
    }

    double calculate_resell_price(double original_price, double age)
    {
        return original_price * (age < 3 ? 0.8 : (age < 10 ? 0.7 : 0.5));
    }

} // namespace vehicle_purchase