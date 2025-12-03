def calculate_total(books):
    groups = []
    for book in books:
        added = False
        for group in groups:
            if book not in group:
                group.append(book)
                added = True
                break
        if not added:
            groups.append([book])

    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    discounts = {
        0: 0,
        1: BOOKCOST,
        2: BOOKCOST * 2 * 0.95,
        3: BOOKCOST * 3 * 0.90,
        4: BOOKCOST * 4 * 0.80,
        5: BOOKCOST * 5 * 0.75
    }
    return sum(discounts.get(len(group), 0) for group in groups)