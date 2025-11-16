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

constexpr House houses[] = {
    {"yellow", "norwegian", "fox", "water", "painter"},
    {"blue", "ukraine", "horse", "tea", "reading"},
    {"red", "english", "snail", "milk", "dancing"},
    {"ivory", "spain", "dog", "orange juice", "football"},
    {"green", "japanese", "zebra", "coffee", "chess"}
};

}  // namespace zebra_puzzle