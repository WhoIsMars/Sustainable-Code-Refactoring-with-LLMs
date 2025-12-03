def latest(scores):
    return scores[-1]


def personal_best(scores):
    return max(scores) if scores else None


def personal_top_three(scores):
    return sorted(scores, reverse=True)[:3] if scores else []