def find_minimum_coins(total_change, coins):
    if total_change == 0:
        return []
    
    coins = sorted(coins, reverse=True)
    dp = [float('inf')] * (total_change + 1)
    parent = [-1] * (total_change + 1)
    coin_used = [-1] * (total_change + 1)
    dp[0] = 0
    
    for amount in range(1, total_change + 1):
        for coin in coins:
            if coin <= amount and dp[amount - coin] + 1 < dp[amount]:
                dp[amount] = dp[amount - coin] + 1
                parent[amount] = amount - coin
                coin_used[amount] = coin
    
    if dp[total_change] == float('inf'):
        raise ValueError("Cannot make chage for {} from {}".format(
            total_change, coins))
    
    result = []
    current = total_change
    while current > 0:
        result.append(coin_used[current])
        current = parent[current]
    
    return result

def fewer(possibly_none, other):
    if possibly_none is None:
        return False 
    return len(possibly_none) < len(other)