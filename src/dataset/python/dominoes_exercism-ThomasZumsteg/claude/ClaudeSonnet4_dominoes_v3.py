def chain(dominoes):
    if not dominoes:
        return []
    
    def can_form_chain(remaining, current_chain, target_start):
        if not remaining:
            return current_chain if current_chain[-1][1] == target_start else None
        
        tail = current_chain[-1][1]
        for i, domino in enumerate(remaining):
            if domino[0] == tail:
                result = can_form_chain(remaining[:i] + remaining[i+1:], current_chain + [domino], target_start)
                if result:
                    return result
            elif domino[1] == tail:
                flipped = (domino[1], domino[0])
                result = can_form_chain(remaining[:i] + remaining[i+1:], current_chain + [flipped], target_start)
                if result:
                    return result
        return None
    
    first_domino = dominoes[0]
    remaining = dominoes[1:]
    
    result = can_form_chain(remaining, [first_domino], first_domino[0])
    if result:
        return tuple(result)
    
    flipped_first = (first_domino[1], first_domino[0])
    result = can_form_chain(remaining, [flipped_first], flipped_first[0])
    return tuple(result) if result else None