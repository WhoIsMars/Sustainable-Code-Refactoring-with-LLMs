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
    return [_verse(n) for n in range(start_verse - 1, end_verse)]


def _verse(n):
    result = ["This is the {}".format(things[n])]
    for i in range(n - 1, -1, -1):
        result.append("that {} the {}".format(actions[i + 1], things[i]))
    return ' '.join(result)