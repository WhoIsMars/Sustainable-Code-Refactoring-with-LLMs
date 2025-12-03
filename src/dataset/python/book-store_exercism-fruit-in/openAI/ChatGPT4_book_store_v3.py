from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    if not basket:
        return 0

    counter = Counter(basket)
    unique_books = len(counter)
    price = float('inf')

    for i in range(1, unique_books + 1):
        group_price = DISCOUNT_PRICE[i]
        remaining_basket = list(counter.elements())
        for book in counter.most_common(i):
            remaining_basket.remove(book[0])
        price = min(price, group_price + total(remaining_basket))

    return price