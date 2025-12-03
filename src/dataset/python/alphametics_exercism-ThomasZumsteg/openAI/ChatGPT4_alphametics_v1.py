from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = {l for word in [result] + words for l in word}
    first_letters = {w[0] for w in words + [result]}
    if len(letters) > 10:
        return {}

    for perm in permutations(range(10), len(letters)):
        combination = dict(zip(letters, perm))
        if any(combination[k] == 0 for k in first_letters):
            continue
        if translate(result, combination) == sum(translate(word, combination) for word in words):
            return combination

    return {}

def translate(word, trans):
    return sum(trans[l] * (10 ** i) for i, l in enumerate(reversed(word)))