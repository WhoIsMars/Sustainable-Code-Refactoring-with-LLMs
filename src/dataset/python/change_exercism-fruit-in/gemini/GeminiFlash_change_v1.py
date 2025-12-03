def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")

    dp = [None] * (target + 1)
    dp[0] = []

    for i in range(target):
        if dp[i] is not None:
            for coin in coins:
                if i + coin <= target:
                    new_len = len(dp[i]) + 1
                    if dp[i + coin] is None or len(dp[i + coin]) > new_len:
                        dp[i + coin] = dp[i] + [coin]

    if target > 0 and dp[target] is None:
        raise ValueError(r".+")

    return sorted(dp[target])