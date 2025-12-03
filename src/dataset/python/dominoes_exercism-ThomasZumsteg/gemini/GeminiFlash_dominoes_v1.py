def chain(dominoes):
    if not dominoes:
        return []

    def find_chain(current_chain, remaining_dominoes):
        if not remaining_dominoes:
            if current_chain[0][0] == current_chain[-1][-1]:
                return current_chain
            else:
                return None

        tail = current_chain[-1][-1]
        for i, domino in enumerate(remaining_dominoes):
            if domino[0] == tail:
                result = find_chain(current_chain + (domino,), remaining_dominoes[:i] + remaining_dominoes[i+1:])
                if result:
                    return result
            if domino[1] == tail:
                result = find_chain(current_chain + ((domino[1], domino[0]),), remaining_dominoes[:i] + remaining_dominoes[i+1:])
                if result:
                    return result
        return None

    return find_chain((dominoes[0],), tuple(dominoes[1:]))