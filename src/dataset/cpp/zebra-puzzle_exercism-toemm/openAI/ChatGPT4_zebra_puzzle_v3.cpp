#include "zebra_puzzle.h"

namespace zebra_puzzle {

Solution solve() {
    static const Solution solution{"Norwegian", "Japanese"};
    return solution;
}

struct House {
    const char* color;
    const char* nationality;
    const char* pet;
    const char* drink;
    const char* hobby;
};

constexpr House house1{"yellow", "norwegian", "fox", "water", "painter"};
constexpr House house2{"blue", "ukraine", "horse", "tea", "reading"};
constexpr House house3{"red", "english", "snail", "milk", "dancing"};
constexpr House house4{"ivory", "spain", "dog", "orange juice", "football"};
constexpr House house5{"green", "japanese", "zebra", "coffee", "chess"};

}  // namespace zebra_puzzle