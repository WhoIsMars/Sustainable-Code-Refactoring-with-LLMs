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

# Pre-compute the spider phrase modification
spider_phrase = "It wriggled and jiggled and tickled inside her."

def recite(start_verse, end_verse):
    result = []
    for n in range(start_verse, end_verse + 1):
        result.extend(verse(n))
        if n < end_verse:
            result.append("")
    return result


def verse(n):
    animal = animals[n - 1]
    ret = [f"I know an old lady who swallowed a {animal}."]
    
    if n > 1:
        ret.append(phrases[n - 2])
    
    if n < 8:
        for i in range(n - 1):
            current_animal = animals[n - i - 1]
            previous_animal = animals[n - i - 2]
            line = f"She swallowed the {current_animal} to catch the {previous_animal}."
            
            if previous_animal == "spider":
                line = f"She swallowed the {current_animal} to catch the spider that {spider_phrase[2:]}"
            
            ret.append(line)
        
        ret.append("I don't know why she swallowed the fly. Perhaps she'll die.")

    return ret