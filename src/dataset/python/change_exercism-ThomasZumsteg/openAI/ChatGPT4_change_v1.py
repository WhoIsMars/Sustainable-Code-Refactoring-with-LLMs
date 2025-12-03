def find_minimum_coins(total_change, coins):
    coins = sorted(coins, reverse=True)
    min_coins = None
    queue = [(total_change, tuple())]
    visited = set()
    
    while queue:
        remaining, change = queue.pop()
        if remaining == 0:
            if min_coins is None or len(change) < len(min_coins):
                min_coins = change
            continue
        if remaining < 0 or (remaining, change) in visited:
            continue
        visited.add((remaining, change))
        for coin in coins:
            queue.append((remaining - coin, change + (coin,)))
    
    if min_coins is None:
        raise ValueError("Cannot make change for {} from {}".format(
            total_change, coins))
    return list(min_coins)

def fewer(possibly_none, other):
    return possibly_none is not None and len(possibly_none) < len(other)