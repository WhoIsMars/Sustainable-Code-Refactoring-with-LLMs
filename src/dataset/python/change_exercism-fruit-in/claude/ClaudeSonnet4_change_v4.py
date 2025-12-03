def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")
    
    if target == 0:
        return []
    
    dp = [float('inf')] * (target + 1)
    dp[0] = 0
    parent = [-1] * (target + 1)
    
    for i in range(target + 1):
        if dp[i] == float('inf'):
            continue
        for coin in coins:
            next_amount = i + coin
            if next_amount <= target and dp[i] + 1 < dp[next_amount]:
                dp[next_amount] = dp[i] + 1
                parent[next_amount] = coin
    
    if dp[target] == float('inf'):
        raise ValueError(r".+")
    
    result = []
    current = target
    while parent[current] != -1:
        coin = parent[current]
        result.append(coin)
        current -= coin
    
    return sorted(result)