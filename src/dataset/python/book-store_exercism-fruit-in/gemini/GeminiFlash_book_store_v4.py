from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    counts = Counter(basket)
    unique_books = len(counts)

    if unique_books == 0:
        return 0

    price = len(basket) * 800

    if unique_books > 1:
        for num_unique in range(2, min(unique_books + 1, 6)):
            discounted_price = DISCOUNT_PRICE[num_unique]
            new_basket = []
            for book, count in counts.items():
                new_count = count - 1
                if new_count > 0:
                    new_basket.extend([book] * new_count)
            price = min(price, discounted_price + total(new_basket))

    return price