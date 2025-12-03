def calculate_total(books):
    if not books:
        return 0
    
    # Count occurrences of each book
    book_counts = {}
    for book in books:
        book_counts[book] = book_counts.get(book, 0) + 1
    
    # Create groups by distributing books optimally
    max_count = max(book_counts.values())
    groups = [[] for _ in range(max_count)]
    
    for book, count in book_counts.items():
        for i in range(count):
            groups[i].append(book)
    
    # Remove empty groups
    groups = [group for group in groups if group]
    
    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    # Pre-calculated discount values to avoid repeated multiplication
    discounts = [0, 800, 1520, 2160, 2560, 3000]
    return sum(discounts[len(group)] for group in groups)