from itertools import permutations

def solve(puzzle):
    words, result = puzzle.split(' == ')
    words = words.split(' + ')
    letters = set(''.join(words) + result)
    first_letters = set(w[0] for w in words + [result])
    
    letter_list = list(letters)
    n = len(letter_list)

    for perm in permutations(range(10), n):
        mapping = dict(zip(letter_list, perm))
        if any(mapping[letter] == 0 and letter in first_letters for letter in letter_list):
            continue
        
        sum_words = sum(translate(word, mapping) for word in words)
        result_val = translate(result, mapping)

        if sum_words == result_val:
            return mapping

    return {}

def translate(word, trans):
    result = 0
    for l in word:
        result = result * 10 + trans[l]
    return result