def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")
    
    if target == 0:
        return []
    
    # Use integers to track minimum coins needed instead of storing actual coins
    dp = [float('inf')] * (target + 1)
    dp[0] = 0
    parent = [-1] * (target + 1)  # Track which coin was used
    
    for i in range(target + 1):
        if dp[i] != float('inf'):
            for coin in coins:
                if i + coin <= target and dp[i] + 1 < dp[i + coin]:
                    dp[i + coin] = dp[i] + 1
                    parent[i + coin] = coin
    
    if dp[target] == float('inf'):
        raise ValueError(r".+")
    
    # Reconstruct the solution
    result = []
    current = target
    while current > 0:
        coin = parent[current]
        result.append(coin)
        current -= coin
    
    return sorted(result)