def calculate_total(books):
    groups = []
    for book in books:
        best_groups = None
        best_cost = float('inf')
        
        # Try adding to existing groups
        for i, group in enumerate(groups):
            if book not in group:
                # Calculate cost without deep copying
                new_cost = _cost_with_addition(groups, i, book)
                if new_cost < best_cost:
                    best_cost = new_cost
                    best_groups = [group[:] for group in groups]
                    best_groups[i].append(book)
        
        # Try creating new group
        new_groups = [group[:] for group in groups] + [[book]]
        new_cost = _cost(new_groups)
        if new_cost < best_cost:
            best_groups = new_groups
        
        groups = [g for g in best_groups if g]
    
    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    discounts = (0, 800, 1520, 2160, 2560, 3000)  # Pre-calculated values
    return sum(discounts[len(group)] for group in groups if group)


def _cost_with_addition(groups, group_index, book):
    BOOKCOST = 800
    discounts = (0, 800, 1520, 2160, 2560, 3000)
    total = 0
    for i, group in enumerate(groups):
        if group:
            size = len(group) + (1 if i == group_index else 0)
            total += discounts[size]
    return total