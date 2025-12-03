def recite(start_verse, end_verse):
    return [verse(v) for v in range(start_verse-1, end_verse)]


animals = (
    ("fly", "", ""),
    ("spider", "It wriggled and jiggled and tickled inside her.",
        " that wriggled and jiggled and tickled inside her"),
    ("bird", "How absurd to swallow a bird!", ""),
    ("cat", "Imagine that, to swallow a cat!", ""),
    ("dog", "What a hog, to swallow a dog!", ""),
    ("goat", "Just opened her throat and swallowed a goat!", ""),
    ("cow", "I don't know how she swallowed a cow!", ""),
    ("horse", "She's dead, of course!", ""),)


end = "I don't know why she swallowed the fly. Perhaps she'll die."

# Pre-compute verse fragments to avoid repeated string operations
_verse_cache = {}

def _build_verse_fragments():
    fragments = {}
    for v in range(8):
        animal_name, reaction, suffix = animals[v]
        opening = f"I know an old lady who swallowed a {animal_name}.{reaction}"
        
        if v == 7:
            fragments[v] = opening
        else:
            catch_lines = []
            for i in range(v, 0, -1):
                catch_lines.append(f"She swallowed the {animals[i][0]} to catch the {animals[i-1][0]}{animals[i-1][2]}.")
            fragments[v] = opening + ''.join(catch_lines) + end
    return fragments

_verse_cache = _build_verse_fragments()

def verse(v):
    return _verse_cache[v]