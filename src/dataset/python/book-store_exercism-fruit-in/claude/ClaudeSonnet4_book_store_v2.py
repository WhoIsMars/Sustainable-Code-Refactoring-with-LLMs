from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]

def total(basket):
    if not basket:
        return 0
    
    counter = Counter(basket)
    memo = {}
    
    def calculate_price(counts_tuple):
        if counts_tuple in memo:
            return memo[counts_tuple]
        
        if not counts_tuple:
            return 0
        
        total_books = sum(counts_tuple)
        price = total_books * 800
        
        unique_books = len(counts_tuple)
        
        for i in range(2, min(unique_books + 1, len(DISCOUNT_PRICE))):
            remaining_counts = tuple(max(0, count - 1) for count in counts_tuple)
            remaining_counts = tuple(c for c in remaining_counts if c > 0)
            
            price = min(price, DISCOUNT_PRICE[i] + calculate_price(remaining_counts))
        
        memo[counts_tuple] = price
        return price
    
    counts_tuple = tuple(sorted(counter.values(), reverse=True))
    return calculate_price(counts_tuple)