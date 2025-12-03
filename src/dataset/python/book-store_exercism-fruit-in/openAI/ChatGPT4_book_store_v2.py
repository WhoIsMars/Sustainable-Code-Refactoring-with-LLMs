from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]

def total(basket):
    if not basket:
        return 0

    counter = Counter(basket)
    unique_books = len(counter)
    price = len(basket) * 800

    for i in range(2, unique_books + 1):
        group_price = DISCOUNT_PRICE[i]
        remaining_basket = basket[:]
        for book, _ in counter.most_common(i):
            remaining_basket.remove(book)
        price = min(price, group_price + total(remaining_basket))

    return price