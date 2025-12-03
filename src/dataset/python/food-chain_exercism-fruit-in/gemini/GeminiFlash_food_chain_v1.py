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

spider_phrase = " that" + phrases[0][2:]
fly_phrase = "I don't know why she swallowed the fly. Perhaps she'll die."


def verse(n):
    ret = ["I know an old lady who swallowed a {}.".format(animals[n - 1])]
    if n > 1:
        ret.append(phrases[n - 2])
    if n < 8:
        for i in range(n - 1):
            swallowed = animals[n - i - 1]
            to_catch = animals[n - i - 2]
            phrase = "She swallowed the {} to catch the {}.".format(swallowed, to_catch)
            if swallowed == "spider":
                phrase = phrase[:-1] + spider_phrase
            ret.append(phrase)
        ret.append(fly_phrase)

    return ret


def recite(start_verse, end_verse):
    ret = []
    for n in range(start_verse, end_verse + 1):
        ret.extend(verse(n))
        ret.append("")

    return ret[:-1]