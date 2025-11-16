#include "knapsack.h"

#include <algorithm>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items){
    if (items.empty() || max_weight <= 0) {
        return 0;
    }

    const int n = items.size();
    std::vector<int> dp(max_weight + 1, 0);

    for (int i = 0; i < n; i++) {
        const int weight = items[i].weight;
        const int value = items[i].value;
        
        for (int w = max_weight; w >= weight; w--) {
            dp[w] = std::max(dp[w], dp[w - weight] + value);
        }
    }

    return dp[max_weight];
}

}  // namespace knapsack