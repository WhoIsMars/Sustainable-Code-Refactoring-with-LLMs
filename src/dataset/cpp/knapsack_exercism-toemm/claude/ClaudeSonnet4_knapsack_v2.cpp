#include "knapsack.h"

#include <algorithm>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items){
    if (items.empty() || max_weight <= 0) return 0;
    
    const int n = items.size();
    
    // Use single dimension DP array with space optimization
    std::vector<int> dp(max_weight + 1, 0);
    
    for (int i = 0; i < n; i++) {
        const auto& item = items[i];
        const int weight = item.weight;
        const int value = item.value;
        
        // Traverse backwards to avoid using updated values
        for (int w = max_weight; w >= weight; w--) {
            dp[w] = std::max(dp[w], dp[w - weight] + value);
        }
    }
    
    return dp[max_weight];
}

}  // namespace knapsack