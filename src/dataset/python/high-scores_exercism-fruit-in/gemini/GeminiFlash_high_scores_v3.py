def latest(scores):
    return scores[-1] if scores else None


def personal_best(scores):
    if not scores:
        return None
    best = scores[0]
    for score in scores[1:]:
        if score > best:
            best = score
    return best


def personal_top_three(scores):
    import heapq
    return heapq.nlargest(3, scores)