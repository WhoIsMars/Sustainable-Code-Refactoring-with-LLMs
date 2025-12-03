from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    if not basket:
        return 0
    
    counter = Counter(basket)
    n_books = len(basket)
    n_unique = len(counter)
    
    if n_unique == 1:
        return n_books * 800
    
    memo = {}
    
    def calculate_min_price(counts_tuple):
        if counts_tuple in memo:
            return memo[counts_tuple]
        
        counts = list(counts_tuple)
        total_books = sum(counts)
        
        if total_books == 0:
            return 0
        
        if len([c for c in counts if c > 0]) <= 1:
            memo[counts_tuple] = total_books * 800
            return memo[counts_tuple]
        
        min_price = total_books * 800
        
        for group_size in range(2, min(len(counts) + 1, len(DISCOUNT_PRICE))):
            if sum(1 for c in counts if c > 0) >= group_size:
                new_counts = counts[:]
                books_taken = 0
                
                for i in range(len(new_counts)):
                    if new_counts[i] > 0 and books_taken < group_size:
                        new_counts[i] -= 1
                        books_taken += 1
                
                remaining_price = calculate_min_price(tuple(new_counts))
                total_price = DISCOUNT_PRICE[group_size] + remaining_price
                min_price = min(min_price, total_price)
        
        memo[counts_tuple] = min_price
        return min_price
    
    counts_tuple = tuple(sorted(counter.values(), reverse=True))
    return calculate_min_price(counts_tuple)