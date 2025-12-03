def recite(start_verse, end_verse):
    return [verse(v) for v in range(start_verse, end_verse + 1)]


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
    lines = [f"I know an old lady who swallowed a {animals[v-1][0]}."]
    lines.append(animals[v-1][1])

    if v == 8:
        return ''.join(lines)

    for i in range(v-1, 1, -1):
        lines.append(f"She swallowed the {animals[i][0]} to catch the {animals[i-1][0]}{animals[i-1][2]}.")

    lines.append(f"She swallowed the {animals[1][0]} to catch the {animals[0][0]}{animals[0][2]}.")
    return ''.join(lines) + end