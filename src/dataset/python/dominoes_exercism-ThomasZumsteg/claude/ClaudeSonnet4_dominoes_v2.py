def chain(dominoes):
    if not dominoes:
        return []
    
    def backtrack(chain, used, target_start):
        if len(chain) == len(dominoes):
            return chain if chain[-1][1] == target_start else None
        
        tail = chain[-1][1]
        for i, domino in enumerate(dominoes):
            if used[i]:
                continue
            
            if domino[0] == tail:
                used[i] = True
                chain.append(domino)
                result = backtrack(chain, used, target_start)
                if result:
                    return result
                chain.pop()
                used[i] = False
            elif domino[1] == tail:
                used[i] = True
                chain.append((domino[1], domino[0]))
                result = backtrack(chain, used, target_start)
                if result:
                    return result
                chain.pop()
                used[i] = False
        
        return None
    
    used = [False] * len(dominoes)
    used[0] = True
    result = backtrack([dominoes[0]], used, dominoes[0][0])
    return list(result) if result else []