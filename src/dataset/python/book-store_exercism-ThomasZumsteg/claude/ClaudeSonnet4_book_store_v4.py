def calculate_total(books):
    if not books:
        return 0
    
    groups = []
    for book in books:
        best_groups = None
        best_cost = float('inf')
        
        for i, group in enumerate(groups):
            if book not in group:
                new_cost = _cost_with_addition(groups, i, book)
                if new_cost < best_cost:
                    best_cost = new_cost
                    best_groups = [group[:] for group in groups]
                    best_groups[i].append(book)
        
        new_group_cost = _cost(groups + [[book]])
        if new_group_cost <= best_cost:
            groups.append([book])
        else:
            groups = best_groups
    
    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    discounts = (0, 800, 1520, 2160, 2560, 3000)
    return sum(discounts[len(group)] for group in groups if group)


def _cost_with_addition(groups, group_index, book):
    BOOKCOST = 800
    discounts = (0, 800, 1520, 2160, 2560, 3000)
    total = 0
    for i, group in enumerate(groups):
        if group:
            if i == group_index:
                total += discounts[len(group) + 1]
            else:
                total += discounts[len(group)]
    return total