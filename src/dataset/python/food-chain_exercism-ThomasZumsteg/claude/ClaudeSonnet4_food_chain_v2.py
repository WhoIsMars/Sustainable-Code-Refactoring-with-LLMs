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


def verse(v):
    animal_name, reaction, suffix = animals[v]
    words = [f"I know an old lady who swallowed a {animal_name}.", reaction]
    
    if v == 7:
        return ''.join(words)

    for i in range(v-1, -1, -1):
        words.append(f"She swallowed the {animals[i+1][0]} to catch the {animals[i][0]}{animals[i][2]}.")

    words.append(end)
    return ''.join(words)