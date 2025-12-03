def chain(dominoes):
    if not dominoes:
        return []
    
    n = len(dominoes)
    if n == 1:
        return dominoes if dominoes[0][0] == dominoes[0][1] else []
    
    def backtrack(current_chain, used_mask, tail_value):
        if len(current_chain) == n:
            return current_chain if current_chain[0][0] == tail_value else None
        
        for i in range(n):
            if used_mask & (1 << i):
                continue
                
            domino = dominoes[i]
            if domino[0] == tail_value:
                result = backtrack(current_chain + [domino], used_mask | (1 << i), domino[1])
                if result:
                    return result
            elif domino[1] == tail_value:
                flipped = (domino[1], domino[0])
                result = backtrack(current_chain + [flipped], used_mask | (1 << i), domino[0])
                if result:
                    return result
        
        return None
    
    first_domino = dominoes[0]
    result = backtrack([first_domino], 1, first_domino[1])
    if result:
        return result
    
    flipped_first = (first_domino[1], first_domino[0])
    result = backtrack([flipped_first], 1, first_domino[0])
    return result if result else []