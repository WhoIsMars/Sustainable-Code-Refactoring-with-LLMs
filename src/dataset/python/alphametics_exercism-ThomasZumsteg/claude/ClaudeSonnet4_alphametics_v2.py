from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(l for word in [result] + words for l in word)
    first_letters = set(w[0] for w in words + [result])
    
    # Pre-compute word multipliers for faster translation
    word_multipliers = []
    for word in words:
        multipliers = []
        power = 1
        for i in range(len(word) - 1, -1, -1):
            multipliers.append((word[i], power))
            power *= 10
        word_multipliers.append(multipliers)
    
    result_multipliers = []
    power = 1
    for i in range(len(result) - 1, -1, -1):
        result_multipliers.append((result[i], power))
        power *= 10
    
    letters_list = list(letters)
    
    for perm in permutations(range(10), len(letters_list)):
        # Quick check for leading zeros
        skip = False
        for i, letter in enumerate(letters_list):
            if letter in first_letters and perm[i] == 0:
                skip = True
                break
        if skip:
            continue
        
        # Fast translation using pre-computed multipliers
        words_sum = 0
        for multipliers in word_multipliers:
            word_value = 0
            for letter, mult in multipliers:
                word_value += perm[letters_list.index(letter)] * mult
            words_sum += word_value
        
        result_value = 0
        for letter, mult in result_multipliers:
            result_value += perm[letters_list.index(letter)] * mult
        
        if result_value == words_sum:
            return dict(zip(letters_list, perm))
    
    return {}

def combinations(keys, values):
    for perm in permutations(values, len(keys)):
        yield dict(zip(keys, list(values[p] for p in perm)))

def translate(word, trans):
    result = 0 
    for l in word:
        result = result * 10 + trans[l]
    return result