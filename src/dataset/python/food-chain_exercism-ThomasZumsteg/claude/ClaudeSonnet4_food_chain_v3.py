def recite(start_verse, end_verse):
    return [verse(v) for v in range(start_verse-1, end_verse)]


ANIMALS = (
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

END = "I don't know why she swallowed the fly. Perhaps she'll die."

_verse_cache = {}

def verse(v):
    if v in _verse_cache:
        return _verse_cache[v]
    
    animal, reaction, suffix = ANIMALS[v]
    words = [f"I know an old lady who swallowed a {animal}.", reaction]
    
    if v == 7:
        result = ''.join(words)
    else:
        for i in range(v-1, -1, -1):
            next_animal = ANIMALS[i+1][0]
            current_animal, _, current_suffix = ANIMALS[i]
            words.append(f"She swallowed the {next_animal} to catch the {current_animal}{current_suffix}.")
        result = ''.join(words) + END
    
    _verse_cache[v] = result
    return result