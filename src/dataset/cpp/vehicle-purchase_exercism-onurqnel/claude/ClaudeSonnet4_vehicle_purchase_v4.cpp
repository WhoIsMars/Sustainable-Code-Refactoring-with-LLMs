#include "vehicle_purchase.h"

namespace vehicle_purchase
{

    bool needs_license(const std::string& kind)
    {
        return kind == "car" || kind == "truck";
    }

    std::string choose_vehicle(const std::string& option1, const std::string& option2)
    {
        const std::string& chosen = (option1 < option2) ? option1 : option2;
        chosen.reserve(chosen.size() + 32);
        return chosen + " is clearly the better choice.";
    }

    double calculate_resell_price(double original_price, double age)
    {
        if (age < 3.0)
        {
            return original_price * 0.80;
        }
        else if (age < 10.0)
        {
            return original_price * 0.70;
        }
        else
        {
            return original_price * 0.50;
        }
    }

}