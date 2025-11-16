#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items) {
    const int n = items.size();
    std::vector<int> dp(max_weight + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int w = max_weight; w >= items[i].weight; --w) {
            dp[w] = std::max(dp[w], dp[w - items[i].weight] + items[i].value);
        }
    }

    return dp[max_weight];
}

}  // namespace knapsack