actions = [
    "lay in",
    "ate",
    "killed",
    "worried",
    "tossed",
    "milked",
    "kissed",
    "married",
    "woke",
    "kept",
    "belonged to",
    "",
]
things = [
    "house that Jack built.",
    "malt",
    "rat",
    "cat",
    "dog",
    "cow with the crumpled horn",
    "maiden all forlorn",
    "man all tattered and torn",
    "priest all shaven and shorn",
    "rooster that crowed in the morn",
    "farmer sowing his corn",
    "horse and the hound and the horn",
]


def recite(start_verse, end_verse):
    return [' '.join(verse_lines(n)) for n in range(start_verse - 1, end_verse)]


def verse_lines(n):
    lines = ["This is the {}".format(things[n])]
    lines.extend(f"that {actions[i]} the {things[i]}" for i in range(n - 1, -1, -1))
    return lines