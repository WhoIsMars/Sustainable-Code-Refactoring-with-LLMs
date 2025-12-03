def find_minimum_coins(total_change, coins):
    coins = sorted(coins, reverse=True)
    min_coins = None
    queue = [(total_change, [])]

    while queue:
        remaining, change = queue.pop()

        if remaining == 0:
            if min_coins is None or len(change) < len(min_coins):
                min_coins = change
            continue

        if min_coins is not None and len(change) >= len(min_coins):
            continue

        for coin in coins:
            if coin <= remaining:
                new_change = change + [coin]
                queue.append((remaining - coin, new_change))
            elif coin > remaining:
                continue
    
    if min_coins is None:
        raise ValueError("Cannot make change for {} from {}".format(total_change, coins))
    return min_coins