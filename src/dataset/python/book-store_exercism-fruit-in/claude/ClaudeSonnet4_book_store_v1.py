from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    if not basket:
        return 0
    
    counter = Counter(basket)
    memo = {}
    
    def _total_recursive(counter_tuple):
        if counter_tuple in memo:
            return memo[counter_tuple]
        
        if not counter_tuple:
            return 0
        
        counter = Counter(dict(counter_tuple))
        total_books = sum(counter.values())
        
        if total_books == 0:
            return 0
        
        price = total_books * 800
        
        max_groups = min(len(DISCOUNT_PRICE) - 1, len(counter))
        
        for group_size in range(2, max_groups + 1):
            if len(counter) >= group_size:
                remaining_counter = counter.copy()
                for book in list(remaining_counter.keys())[:group_size]:
                    remaining_counter[book] -= 1
                    if remaining_counter[book] == 0:
                        del remaining_counter[book]
                
                remaining_tuple = tuple(sorted(remaining_counter.items()))
                price = min(price, DISCOUNT_PRICE[group_size] + _total_recursive(remaining_tuple))
        
        memo[counter_tuple] = price
        return price
    
    counter_tuple = tuple(sorted(counter.items()))
    return _total_recursive(counter_tuple)