from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(''.join(words) + result)
    first_letters = set(w[0] for w in words + [result])
    
    letter_list = list(letters)
    num_letters = len(letter_list)

    for digits in permutations(range(10), num_letters):
        mapping = dict(zip(letter_list, digits))
        
        if any(mapping[letter] == 0 for letter in first_letters):
            continue
        
        sum_words = sum(translate(word, mapping) for word in words)
        result_val = translate(result, mapping)
        
        if sum_words == result_val:
            return mapping

    return {}

def translate(word, mapping):
    num = 0
    for char in word:
        num = num * 10 + mapping[char]
    return num