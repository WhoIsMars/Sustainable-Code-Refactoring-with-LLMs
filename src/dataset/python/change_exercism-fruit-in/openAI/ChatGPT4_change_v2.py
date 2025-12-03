def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")

    dp = [float('inf')] * (target + 1)
    dp[0] = 0
    backtrack = [-1] * (target + 1)

    for coin in coins:
        for i in range(coin, target + 1):
            if dp[i - coin] + 1 < dp[i]:
                dp[i] = dp[i - coin] + 1
                backtrack[i] = coin

    if dp[target] == float('inf'):
        raise ValueError(r".+")

    result = []
    while target > 0:
        result.append(backtrack[target])
        target -= backtrack[target]

    return sorted(result)