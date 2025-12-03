animals = ("fly", "spider", "bird", "cat", "dog", "goat", "cow", "horse")
phrases = (
    "It wriggled and jiggled and tickled inside her.",
    "How absurd to swallow a bird!",
    "Imagine that, to swallow a cat!",
    "What a hog, to swallow a dog!",
    "Just opened her throat and swallowed a goat!",
    "I don't know how she swallowed a cow!",
    "She's dead, of course!",
)

_SPIDER_SUFFIX = " that wriggled and jiggled and tickled inside her."
_FLY_ENDING = "I don't know why she swallowed the fly. Perhaps she'll die."


def recite(start_verse, end_verse):
    result = []
    for n in range(start_verse, end_verse + 1):
        result.extend(verse(n))
        if n < end_verse:
            result.append("")
    return result


def verse(n):
    animal = animals[n - 1]
    result = [f"I know an old lady who swallowed a {animal}."]
    
    if n > 1:
        result.append(phrases[n - 2])
    
    if n < 8:
        for i in range(n - 1, 0, -1):
            line = f"She swallowed the {animals[i]} to catch the {animals[i - 1]}."
            if animals[i - 1] == "spider":
                line = line[:-1] + _SPIDER_SUFFIX
            result.append(line)
        result.append(_FLY_ENDING)
    
    return result