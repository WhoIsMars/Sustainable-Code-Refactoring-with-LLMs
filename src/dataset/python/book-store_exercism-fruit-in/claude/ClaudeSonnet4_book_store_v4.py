from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]

def total(basket):
    if not basket:
        return 0
    
    counter = Counter(basket)
    num_unique = len(counter)
    
    if num_unique == 1:
        return len(basket) * 800
    
    memo = {}
    
    def calculate_min_price(counts_tuple):
        if counts_tuple in memo:
            return memo[counts_tuple]
        
        counts = list(counts_tuple)
        total_books = sum(counts)
        
        if total_books == 0:
            return 0
        
        min_price = total_books * 800
        
        for group_size in range(2, min(len(DISCOUNT_PRICE), len([c for c in counts if c > 0]) + 1)):
            new_counts = []
            books_in_group = 0
            
            for count in counts:
                if count > 0 and books_in_group < group_size:
                    new_counts.append(count - 1)
                    books_in_group += 1
                else:
                    new_counts.append(count)
            
            if books_in_group == group_size:
                remaining_price = calculate_min_price(tuple(new_counts))
                min_price = min(min_price, DISCOUNT_PRICE[group_size] + remaining_price)
        
        memo[counts_tuple] = min_price
        return min_price
    
    counts_tuple = tuple(sorted(counter.values(), reverse=True))
    return calculate_min_price(counts_tuple)