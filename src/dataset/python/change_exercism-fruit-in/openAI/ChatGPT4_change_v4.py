def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")

    dp = [None] * (target + 1)
    dp[0] = []

    for i in range(target + 1):
        if dp[i] is not None:
            for coin in coins:
                next_target = i + coin
                if next_target <= target and (dp[next_target] is None or len(dp[next_target]) > len(dp[i]) + 1):
                    dp[next_target] = dp[i] + [coin]

    if dp[target] is None:
        raise ValueError(r".+")

    return sorted(dp[target])