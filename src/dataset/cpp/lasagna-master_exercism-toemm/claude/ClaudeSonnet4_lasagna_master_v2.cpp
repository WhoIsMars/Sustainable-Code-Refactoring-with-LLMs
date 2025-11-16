#include "lasagna_master.h"

#include <vector>
#include <string>

namespace lasagna_master {

int preparationTime(const std::vector<std::string>& vec, int prep_time) {
    return static_cast<int>(vec.size()) * prep_time;
}

void addSecretIngredient(std::vector<std::string>& own_list, const std::vector<std::string>& friends_list) {
    own_list.back() = friends_list.back();
}

void addSecretIngredient(std::vector<std::string>& own_list, const std::string& secret_ingredient) {
    own_list.back() = secret_ingredient;
}

std::vector<double> scaleRecipe(const std::vector<double>& quantities, int nr) {
    std::vector<double> new_quantities;
    new_quantities.reserve(quantities.size());
    
    const double scale_factor = nr * 0.5;
    for (const auto& quantity : quantities) {
        new_quantities.push_back(quantity * scale_factor);
    }
    
    return new_quantities;
}

amount quantities(const std::vector<std::string>& vec) {
    amount amounts{0, 0.0};
    
    for (const auto& layer : vec) {
        if (layer == "sauce") {
            amounts.sauce += 0.2;
        } else if (layer == "noodles") {
            amounts.noodles += 50;
        }
    }
    
    return amounts;
}

}  // namespace lasagna_master