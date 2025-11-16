#include "vehicle_purchase.h"

namespace vehicle_purchase
{

    bool needs_license(const std::string& kind)
    {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string& option1, const std::string& option2)
    {
        const std::string& option = (option1 < option2) ? option1 : option2;
        std::string result;
        result.reserve(option.length() + 27);
        result = option + " is clearly the better choice.";
        return result;
    }

    double calculate_resell_price(double original_price, double age)
    {
        if (age < 3.0)
        {
            return original_price * 0.8;
        }
        else if (age < 10.0)
        {
            return original_price * 0.7;
        }
        return original_price * 0.5;
    }

}