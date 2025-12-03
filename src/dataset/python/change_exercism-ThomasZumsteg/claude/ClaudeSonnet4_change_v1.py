def find_minimum_coins(total_change, coins):
    if total_change == 0:
        return []
    
    # Sort coins in descending order for better pruning
    sorted_coins = sorted(coins, reverse=True)
    
    # Use dynamic programming with memoization
    memo = {}
    
    def dp(remaining):
        if remaining == 0:
            return []
        if remaining < 0:
            return None
        if remaining in memo:
            return memo[remaining]
        
        best = None
        for coin in sorted_coins:
            if coin <= remaining:
                sub_result = dp(remaining - coin)
                if sub_result is not None:
                    candidate = [coin] + sub_result
                    if best is None or len(candidate) < len(best):
                        best = candidate
        
        memo[remaining] = best
        return best
    
    result = dp(total_change)
    if result is None:
        raise ValueError("Cannot make chage for {} from {}".format(
            total_change, coins))
    return result

def fewer(possibly_none, other):
    if possibly_none is None:
        return False 
    return len(possibly_none) < len(other)