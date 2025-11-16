#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items) {
    const int rows = items.size() + 1;
    const int cols = max_weight + 1;

    // Use a single-dimensional array to reduce memory usage
    std::vector<int> dp(cols, 0);

    for (const auto& item : items) {
        int item_weight = item.weight;
        int item_value = item.value;

        // Traverse dp array in reverse to avoid overwriting values prematurely
        for (int j = max_weight; j >= item_weight; --j) {
            dp[j] = std::max(dp[j], dp[j - item_weight] + item_value);
        }
    }

    return dp[max_weight];
}

}  // namespace knapsack