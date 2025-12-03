def calculate_total(books):
    groups = []
    for book in books:
        best_group_index = -1
        min_cost = float('inf')

        for i, group in enumerate(groups):
            if book not in group:
                temp_group = group + [book]
                cost = _cost([temp_group] + groups[:i] + groups[i+1:])
                if cost < min_cost:
                    min_cost = cost
                    best_group_index = i

        if best_group_index != -1:
            groups[best_group_index].append(book)
        else:
            groups.append([book])

    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    discounts = {
        0: 0,
        1: 1,
        2: 0.95,
        3: 0.90,
        4: 0.80,
        5: 0.75
    }
    total_cost = 0
    for group in groups:
        discount = discounts.get(len(group), 1)
        total_cost += len(group) * BOOKCOST * discount
    return total_cost