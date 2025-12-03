def find_fewest_coins(coins, target):
    if target < 0:
        raise ValueError(r".+")

    dp = [None] * (target + 1)
    dp[0] = []

    for i in range(target):
        if dp[i] is not None:
            for coin in coins:
                new_target = i + coin
                if new_target <= target:
                    new_combination = dp[i] + [coin]
                    if dp[new_target] is None or len(dp[new_target]) > len(new_combination):
                        dp[new_target] = new_combination

    if target > 0 and dp[target] is None:
        raise ValueError(r".+")

    return sorted(dp[target])