def calculate_total(books):
    unique_books = set(books)
    groups = []
    while unique_books:
        group = set()
        for book in list(unique_books):
            group.add(book)
            unique_books.remove(book)
        groups.append(group)
    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    discounts = {
        1: 1 * BOOKCOST * 1,
        2: 2 * BOOKCOST * 0.95,
        3: 3 * BOOKCOST * 0.90,
        4: 4 * BOOKCOST * 0.80,
        5: 5 * BOOKCOST * 0.75
    }
    return sum(discounts.get(len(group), 0) for group in groups)