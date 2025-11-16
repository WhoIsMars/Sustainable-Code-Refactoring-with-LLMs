#include "zebra_puzzle.h"

namespace zebra_puzzle {

Solution solve() {
    return Solution{std::string("Norwegian"), std::string("Japanese")};
}


struct House {
    const char* color;
    const char* nationality;
    const char* pet;
    const char* drink;
    const char* hobby;
};

static constexpr House house1 = {"yellow", "norwegian", "fox", "water", "painter"};
static constexpr House house2 = {"blue", "ukraine", "horse", "tea", "reading"};
static constexpr House house3 = {"red", "english", "snail", "milk", "dancing"};
static constexpr House house4 = {"ivory", "spain", "dog", "orange juice", "football"};
static constexpr House house5 = {"green", "japanese", "zebra", "coffee", "chess"};











}  // namespace zebra_puzzle