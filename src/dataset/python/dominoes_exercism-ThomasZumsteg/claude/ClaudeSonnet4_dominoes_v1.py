def chain(dominoes):
    if not dominoes:
        return []
    
    def backtrack(chain, used, remaining):
        if not remaining:
            if chain[0][0] == chain[-1][1]:
                return chain
            return None
        
        tail = chain[-1][1]
        for i, domino in enumerate(remaining):
            if used[i]:
                continue
                
            # Try domino as is
            if domino[0] == tail:
                used[i] = True
                result = backtrack(chain + [domino], used, remaining)
                if result:
                    return result
                used[i] = False
            
            # Try flipped domino
            if domino[1] == tail:
                flipped = (domino[1], domino[0])
                used[i] = True
                result = backtrack(chain + [flipped], used, remaining)
                if result:
                    return result
                used[i] = False
        
        return None
    
    used = [False] * len(dominoes)
    for i, start_domino in enumerate(dominoes):
        # Try starting with domino as is
        used[i] = True
        result = backtrack([start_domino], used, dominoes)
        if result:
            return result
        used[i] = False
        
        # Try starting with flipped domino
        flipped_start = (start_domino[1], start_domino[0])
        used[i] = True
        result = backtrack([flipped_start], used, dominoes)
        if result:
            return result
        used[i] = False
    
    return []