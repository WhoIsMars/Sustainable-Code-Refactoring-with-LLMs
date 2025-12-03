from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    counts = Counter(basket)
    num_books = len(counts)
    
    if num_books == 0:
        return 0

    price = len(basket) * 800

    for i in range(2, min(6, num_books + 1)):
        price = min(price, DISCOUNT_PRICE[i] + total((basket[:len(basket) - i])))
        
    return price