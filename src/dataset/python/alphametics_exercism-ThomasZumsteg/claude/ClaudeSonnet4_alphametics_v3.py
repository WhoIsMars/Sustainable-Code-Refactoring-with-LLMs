from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(l for word in [result] + words for l in word)
    first_letters = set(w[0] for w in words + [result])
    
    letters_list = list(letters)
    n_letters = len(letters_list)
    
    if n_letters > 10:
        return {}
    
    for perm in permutations(range(10), n_letters):
        combination = dict(zip(letters_list, perm))
        
        if any(combination[letter] == 0 for letter in first_letters):
            continue
            
        if translate(result, combination) == sum(
                translate(word, combination) for word in words):
            return combination

    return {}

def combinations(keys, values):
    keys_list = list(keys)
    for perm in permutations(values, len(keys_list)):
        yield dict(zip(keys_list, perm))

def translate(word, trans):
    result = 0 
    for l in word:
        result = result * 10 + trans[l]
    return result