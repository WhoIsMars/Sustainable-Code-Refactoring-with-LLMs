def chain(dominoes):
    if not dominoes:
        return []
    
    def backtrack(chain, pool):
        if chain[0][0] == chain[-1][-1] and not pool:
            return chain
        tail = chain[-1][-1]
        for i, domino in enumerate(pool):
            if domino[0] == tail or domino[1] == tail:
                next_domino = domino if domino[0] == tail else (domino[1], domino[0])
                result = backtrack(chain + (next_domino,), pool[:i] + pool[i+1:])
                if result:
                    return result
        return None

    return backtrack((dominoes[0],), tuple(dominoes[1:]))