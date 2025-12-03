from collections import deque

def chain(dominoes):
    if not dominoes:
        return []
    queue = deque([((dominoes[0],), tuple(dominoes[1:]))])
    while queue:
        chain, pool = queue.popleft()
        tail = chain[-1][1]
        if chain[0][0] == tail and not pool:
            return chain
        for i, domino in enumerate(pool):
            if domino[0] == tail or domino[1] == tail:
                next_domino = domino if domino[0] == tail else (domino[1], domino[0])
                queue.append((chain + (next_domino,), pool[:i] + pool[i+1:]))
    return []