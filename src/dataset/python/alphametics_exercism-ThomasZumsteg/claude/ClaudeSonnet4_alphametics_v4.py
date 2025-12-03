from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = list(set(l for word in [result] + words for l in word))
    first_letters = {w[0] for w in words + [result]}
    
    for perm in permutations(range(10), len(letters)):
        combination = dict(zip(letters, perm))
        if any(combination[letter] == 0 for letter in first_letters):
            continue
        if translate(result, combination) == sum(
                translate(word, combination) for word in words):
            return combination
    
    return {}

def combinations(keys, values):
    for perm in permutations(values, len(keys)):
        yield dict(zip(keys, perm))

def translate(word, trans):
    result = 0 
    for l in word:
        result = result * 10 + trans[l]
    return result