from collections import Counter

DISCOUNT_PRICE = [0, 800, 1520, 2160, 2560, 3000]


def total(basket):
    counts = Counter(basket)
    num_books = len(counts)
    price = len(basket) * 800

    if num_books > 1:
        sets = []
        while True:
            current_set = []
            remaining_books = Counter()
            for book in counts:
                if counts[book] > 0:
                    current_set.append(book)
                    counts[book] -= 1
                else:
                    remaining_books[book] = counts[book]
            if not current_set:
                break
            sets.append(len(current_set))
            counts = +remaining_books #remove zero counts

        sets.sort(reverse=True)
        total_price = 0
        for s in sets:
            total_price += DISCOUNT_PRICE[s]
        price = min(price, total_price)

    return price