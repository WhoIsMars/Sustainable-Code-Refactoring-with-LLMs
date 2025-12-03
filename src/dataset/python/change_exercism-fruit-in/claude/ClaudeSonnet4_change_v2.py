def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")
    
    if target == 0:
        return []
    
    # Use integers to track coin counts instead of storing actual coins
    dp = [float('inf')] * (target + 1)
    parent = [-1] * (target + 1)
    coin_used = [0] * (target + 1)
    
    dp[0] = 0
    
    for i in range(target + 1):
        if dp[i] != float('inf'):
            for coin in coins:
                next_amount = i + coin
                if next_amount <= target and dp[next_amount] > dp[i] + 1:
                    dp[next_amount] = dp[i] + 1
                    parent[next_amount] = i
                    coin_used[next_amount] = coin
    
    if dp[target] == float('inf'):
        raise ValueError(r".+")
    
    # Reconstruct the solution
    result = []
    current = target
    while current > 0:
        result.append(coin_used[current])
        current = parent[current]
    
    return sorted(result)