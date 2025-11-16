#pragma once

#include <vector>
#include <string>

namespace lasagna_master {

struct amount {
    int noodles;
    double sauce;
};

//  arguments to the right of the first default argument need a default value too
int preparationTime(const std::vector<std::string>& vec, int prep_time=2);
amount quantities(const std::vector<std::string>& vec);
void addSecretIngredient(std::vector<std::string>& own_list, const std::vector<std::string>& friends_list);
void addSecretIngredient(std::vector<std::string>& own_list, const std::string& secret_ingredient);
std::vector<double> scaleRecipe(const std::vector<double>& quantities, int nr);

}  // namespace lasagna_master
