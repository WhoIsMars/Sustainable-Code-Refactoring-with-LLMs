from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(result + ''.join(words))
    first_letters = {word[0] for word in words + [result]}
    non_zero_letters = {l for l in first_letters if l in letters}

    if len(letters) > 10:
        return {}

    for perm in permutations(range(10), len(letters)):
        trans = dict(zip(letters, perm))
        if any(trans[l] == 0 for l in non_zero_letters):
            continue
        if translate(result, trans) == sum(translate(word, trans) for word in words):
            return trans

    return {}

def translate(word, trans):
    return sum(trans[l] * (10 ** i) for i, l in enumerate(reversed(word)))