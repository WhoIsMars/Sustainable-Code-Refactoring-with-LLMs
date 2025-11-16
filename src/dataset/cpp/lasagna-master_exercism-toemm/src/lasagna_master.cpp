#include "lasagna_master.h"

#include <vector>
#include <string>
#include <iostream>

namespace lasagna_master {

int preparationTime(const std::vector<std::string>& vec, int prep_time) {
    return vec.size() * prep_time;
}

void addSecretIngredient(std::vector<std::string>& own_list, const std::vector<std::string>& friends_list) {


    //std::cout << "my: " << own_list[own_list.size()-1] << std::endl;
    //std::cout << "friends: " << *(friends_list.cend()-1) << std::endl;
    own_list[own_list.size()-1] = *(friends_list.cend()-1);

}

void addSecretIngredient(std::vector<std::string>& own_list, const std::string& secret_ingredient) {
    const std::vector<std::string> secret_list {secret_ingredient};
    addSecretIngredient(own_list, secret_list);
}


std::vector<double> scaleRecipe(const std::vector<double>& quantities, int nr) {
    std::vector<double> new_quantities;

    for (auto it=quantities.begin(); it != quantities.end(); it++) {
        new_quantities.push_back(*it * nr/2);
    }

    return new_quantities;

}

amount quantities(const std::vector<std::string>& vec) {
   
    amount amounts{0, 0.0};
   
    for (auto layer : vec) {
        if (layer == "sauce") amounts.sauce += 0.2;
        if (layer == "noodles") amounts.noodles += 50;
    }

    return amounts;
}

}  // namespace lasagna_master
