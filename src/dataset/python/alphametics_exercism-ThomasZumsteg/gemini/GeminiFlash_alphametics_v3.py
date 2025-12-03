from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(l for word in [result] + words for l in word)
    first_letters = set(w[0] for w in words + [result])
    letters = list(letters)
    n = len(letters)

    for perm in permutations(range(10), n):
        combination = dict(zip(letters, perm))
        if any(combination[k] == 0 and k in first_letters for k in first_letters):
            continue
        if translate(result, combination) == sum(translate(word, combination) for word in words):
            return combination

    return {}

def translate(word, trans):
    result = 0
    for l in word:
        result = result * 10 + trans[l]
    return result