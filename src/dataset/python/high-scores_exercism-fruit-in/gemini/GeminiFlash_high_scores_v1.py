def latest(scores):
    return scores[-1]


def personal_best(scores):
    if not scores:
        return None  # Handle empty list case
    best = scores[0]
    for score in scores[1:]:
        if score > best:
            best = score
    return best


def personal_top_three(scores):
    # Use nlargest for efficiency, especially for larger lists
    import heapq
    return heapq.nlargest(3, scores)