#include "lasagna_master.h"

#include <vector>
#include <string>
#include <iostream>

namespace lasagna_master {

int preparationTime(const std::vector<std::string>& vec, int prep_time) {
    return static_cast<int>(vec.size()) * prep_time;
}

void addSecretIngredient(std::vector<std::string>& own_list, const std::vector<std::string>& friends_list) {
    if (!own_list.empty() && !friends_list.empty()) {
        own_list.back() = friends_list.back();
    }
}

void addSecretIngredient(std::vector<string>& own_list, const std::string& secret_ingredient) {
    if (!own_list.empty()) {
        own_list.back() = secret_ingredient;
    }
}


std::vector<double> scaleRecipe(const std::vector<double>& quantities, int nr) {
    std::vector<double> new_quantities(quantities.size());
    double factor = static_cast<double>(nr) / 2.0;

    for (size_t i = 0; i < quantities.size(); ++i) {
        new_quantities[i] = quantities[i] * factor;
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