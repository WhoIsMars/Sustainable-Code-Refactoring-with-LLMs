#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items) {
    if (items.empty() || max_weight <= 0) {
        return 0;
    }

    const int n = items.size();
    std::vector<int> prev(max_weight + 1, 0);
    std::vector<int> curr(max_weight + 1, 0);

    for (int i = 0; i < n; ++i) {
        const int weight = items[i].weight;
        const int value = items[i].value;

        for (int w = 0; w <= max_weight; ++w) {
            if (weight > w) {
                curr[w] = prev[w];
            } else {
                curr[w] = std::max(prev[w], prev[w - weight] + value);
            }
        }
        prev.swap(curr);
    }

    return prev[max_weight];
}

}  // namespace knapsack