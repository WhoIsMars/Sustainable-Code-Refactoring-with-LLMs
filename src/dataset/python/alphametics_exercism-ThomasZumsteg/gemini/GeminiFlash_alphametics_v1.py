from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(l for word in [result] + words for l in word)
    first_letters = set(w[0] for w in words + [result])
    letters = list(letters)
    n = len(letters)

    for digits in permutations(range(10), n):
        if any(digits[letters.index(letter)] == 0 and letter in first_letters for letter in letters):
            continue

        translation = dict(zip(letters, digits))
        if translate(result, translation) == sum(translate(word, translation) for word in words):
            return translation

    return {}

def translate(word, trans):
    result = 0
    for l in word:
        result = result * 10 + trans[l]
    return result