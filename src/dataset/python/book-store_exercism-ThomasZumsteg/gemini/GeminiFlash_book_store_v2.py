def calculate_total(books):
    unique_books = set(books)
    book_counts = {}
    for book in books:
        book_counts[book] = book_counts.get(book, 0) + 1

    counts = sorted(book_counts.values(), reverse=True)
    
    total_cost = 0
    while counts:
        group_size = len(counts)
        total_cost += _cost_for_group(group_size)
        counts = [count - 1 for count in counts if count > 1]
        counts.sort(reverse=True)

    return total_cost


def _cost_for_group(n_books):
    BOOKCOST = 800
    if n_books == 0:
        return 0
    elif n_books == 1:
        return BOOKCOST
    elif n_books == 2:
        return 2 * BOOKCOST * 0.95
    elif n_books == 3:
        return 3 * BOOKCOST * 0.90
    elif n_books == 4:
        return 4 * BOOKCOST * 0.80
    elif n_books == 5:
        return 5 * BOOKCOST * 0.75
    else:
        return 0