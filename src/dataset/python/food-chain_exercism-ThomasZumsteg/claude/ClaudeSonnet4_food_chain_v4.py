def recite(start_verse, end_verse):
    return [verse(v) for v in range(start_verse-1, end_verse)]


_ANIMALS = (
    ("fly", "", ""),
    ("spider", "It wriggled and jiggled and tickled inside her.",
        " that wriggled and jiggled and tickled inside her"),
    ("bird", "How absurd to swallow a bird!", ""),
    ("cat", "Imagine that, to swallow a cat!", ""),
    ("dog", "What a hog, to swallow a dog!", ""),
    ("goat", "Just opened her throat and swallowed a goat!", ""),
    ("cow", "I don't know how she swallowed a cow!", ""),
    ("horse", "She's dead, of course!", ""),
)

_END = "I don't know why she swallowed the fly. Perhaps she'll die."

_VERSE_CACHE = {}

def verse(v):
    if v in _VERSE_CACHE:
        return _VERSE_CACHE[v]
    
    animal_data = _ANIMALS[v]
    words = [f"I know an old lady who swallowed a {animal_data[0]}.", animal_data[1]]
    
    if v == 7:
        result = ''.join(words)
    else:
        for i in range(v-1, -1, -1):
            words.append(f"She swallowed the {_ANIMALS[i+1][0]} to catch the {_ANIMALS[i][0]}{_ANIMALS[i][2]}.")
        result = ''.join(words) + _END
    
    _VERSE_CACHE[v] = result
    return result