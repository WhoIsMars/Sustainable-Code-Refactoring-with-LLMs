from collections import deque

def find_minimum_coins(total_change, coins):
    coins = sorted(coins, reverse=True)
    queue = deque([(total_change, [])])
    visited = set()
    
    while queue:
        remaining, change = queue.popleft()
        if remaining == 0:
            return change
        if remaining < 0 or (remaining, tuple(change)) in visited:
            continue
        visited.add((remaining, tuple(change)))
        for coin in coins:
            queue.append((remaining - coin, change + [coin]))
    
    raise ValueError("Cannot make change for {} from {}".format(total_change, coins))

def fewer(possibly_none, other):
    return False  # Function retained for interface compatibility