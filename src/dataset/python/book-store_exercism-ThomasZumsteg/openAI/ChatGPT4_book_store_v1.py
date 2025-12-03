def calculate_total(books):
    from collections import Counter

    def _cost(groups):
        BOOKCOST = 800
        discounts = {1: 1, 2: 0.95, 3: 0.90, 4: 0.80, 5: 0.75}
        return sum(len(group) * BOOKCOST * discounts[len(group)] for group in groups)

    book_counts = Counter(books)
    groups = []

    while book_counts:
        group = []
        for book in list(book_counts.keys()):
            group.append(book)
            book_counts[book] -= 1
            if book_counts[book] == 0:
                del book_counts[book]
        groups.append(group)

    return _cost(groups)