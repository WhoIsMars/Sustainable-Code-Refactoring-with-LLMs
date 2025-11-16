#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items) {
    const int n = items.size();
    std::vector<int> dp(max_weight + 1, 0);

    for (const auto& item : items) {
        for (int j = max_weight; j >= item.weight; --j) {
            dp[j] = std::max(dp[j], dp[j - item.weight] + item.value);
        }
    }

    return dp[max_weight];
}

}  // namespace knapsack