def calculate_total(books):
    if not books:
        return 0
    
    groups = []
    
    for book in books:
        best_groups = None
        best_cost = float('inf')
        
        # Try adding to existing groups
        for i, group in enumerate(groups):
            if book not in group:
                group.append(book)
                cost = _cost(groups)
                if cost < best_cost:
                    best_cost = cost
                    best_groups = [g[:] for g in groups]
                group.pop()
        
        # Try creating new group
        groups.append([book])
        cost = _cost(groups)
        if cost < best_cost:
            best_cost = cost
            best_groups = [g[:] for g in groups]
        groups.pop()
        
        groups = best_groups
    
    return _cost(groups)


def _cost(groups):
    BOOKCOST = 800
    discounts = (0, 800, 1520, 2160, 2560, 3000)
    return sum(discounts[len(group)] for group in groups if group)