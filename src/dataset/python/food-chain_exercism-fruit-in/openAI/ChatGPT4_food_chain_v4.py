animals = ["fly", "spider", "bird", "cat", "dog", "goat", "cow", "horse"]
phrases = [
    "It wriggled and jiggled and tickled inside her.",
    "How absurd to swallow a bird!",
    "Imagine that, to swallow a cat!",
    "What a hog, to swallow a dog!",
    "Just opened her throat and swallowed a goat!",
    "I don't know how she swallowed a cow!",
    "She's dead, of course!",
]

def recite(start_verse, end_verse):
    return [line for n in range(start_verse, end_verse + 1) for line in verse(n)]


def verse(n):
    ret = [f"I know an old lady who swallowed a {animals[n - 1]}."]
    if n > 1:
        ret.append(phrases[n - 2])
    if n < 8:
        ret.extend(
            f"She swallowed the {animals[j]} to catch the {animals[j - 1]}" +
            (f" that{phrases[0][2:]}" if animals[j - 1] == "spider" else ".")
            for j in range(n - 1, 0, -1)
        )
        ret.append("I don't know why she swallowed the fly. Perhaps she'll die.")
    return ret