def find_minimum_coins(total_change, coins):
    coins = sorted(coins, reverse=True)
    dp = [float('inf')] * (total_change + 1)
    coin_counts = [[] for _ in range(total_change + 1)]
    dp[0] = 0
    
    for coin in coins:
        for amount in range(coin, total_change + 1):
            if dp[amount - coin] + 1 < dp[amount]:
                dp[amount] = dp[amount - coin] + 1
                coin_counts[amount] = coin_counts[amount - coin] + [coin]

    if dp[total_change] == float('inf'):
        raise ValueError("Cannot make chage for {} from {}".format(
            total_change, coins))
    return coin_counts[total_change]

def fewer(possibly_none, other):
    if possibly_none is None:
        return False 
    return len(possibly_none) < len(other)