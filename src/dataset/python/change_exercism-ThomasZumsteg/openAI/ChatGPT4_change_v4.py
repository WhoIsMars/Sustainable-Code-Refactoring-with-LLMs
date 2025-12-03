from collections import deque

def find_minimum_coins(total_change, coins):
    coins = sorted(coins, reverse=True)
    queue = deque([(total_change, tuple())])
    visited = set()
    while queue:
        remaining, change = queue.popleft()
        if remaining == 0:
            return list(change)
        if remaining < 0 or (remaining, change) in visited:
            continue
        visited.add((remaining, change))
        for coin in coins:
            queue.append((remaining - coin, change + (coin,)))
    raise ValueError(f"Cannot make change for {total_change} from {coins}")

def fewer(possibly_none, other):
    return possibly_none is not None and len(possibly_none) < len(other)