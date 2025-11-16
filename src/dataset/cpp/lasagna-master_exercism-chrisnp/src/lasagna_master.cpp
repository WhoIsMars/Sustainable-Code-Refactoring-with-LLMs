#include "lasagna_master.h"

namespace lasagna_master {

auto preparationTime(const std::vector<std::string> &layers, int time) -> int 
{
    return time * layers.size();
}

auto quantities(const std::vector<std::string> &layers) -> amount
{
    amount amount {};
    for (auto& ingredient : layers) {
        if (ingredient == "noodles") amount.noodles += 50;
        if (ingredient == "sauce") amount.sauce+= 0.2;
    }
    return amount;
}

void addSecretIngredient(std::vector<std::string> &myList, 
                    const std::vector<std::string> &friendList) {
    myList[myList.size() - 1] = friendList[friendList.size() - 1];
}

void addSecretIngredient(std::vector<std::string> &myList, 
                    const std::string &auntiesSecret) {
    myList[myList.size() - 1] = auntiesSecret;
}

auto scaleRecipe(const std::vector<double>& quantities, int portions) -> std::vector<double> 
{
    std::vector<double> scaledQs {};
    for (auto& q : quantities) {
        scaledQs.push_back(q * portions / 2.0);
    }
    return scaledQs;
}

}  // namespace lasagna_master
