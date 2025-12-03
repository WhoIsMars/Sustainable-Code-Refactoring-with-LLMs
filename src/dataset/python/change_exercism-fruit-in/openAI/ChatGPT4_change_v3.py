def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")

    dp = [None] * (target + 1)
    dp[0] = []

    for coin in coins:
        for i in range(coin, target + 1):
            if dp[i - coin] is not None and (dp[i] is None or len(dp[i]) > len(dp[i - coin]) + 1):
                dp[i] = dp[i - coin] + [coin]

    if dp[target] is None:
        raise ValueError(r".+")

    return sorted(dp[target])