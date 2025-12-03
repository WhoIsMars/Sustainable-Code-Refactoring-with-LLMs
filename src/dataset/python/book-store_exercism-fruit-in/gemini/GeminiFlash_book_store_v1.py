from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    counts = Counter(basket)
    num_books = len(counts)

    if num_books == 0:
        return 0

    price = len(basket) * 800

    for i in range(2, min(num_books + 1, 6)):
        discounted_price = DISCOUNT_PRICE[i]
        remaining_books = []
        
        most_common = counts.most_common(i)
        
        temp_counts = counts.copy()
        for book, _ in most_common:
            temp_counts[book] -= 1
            if temp_counts[book] == 0:
                del temp_counts[book]
        
        for book, count in temp_counts.items():
            remaining_books.extend([book] * count)
        
        price = min(price, discounted_price + total(remaining_books))

    return price