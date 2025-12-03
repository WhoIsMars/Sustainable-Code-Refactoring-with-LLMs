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

SPIDER_SUFFIX = " that wriggled and jiggled and tickled inside her."
FLY_ENDING = "I don't know why she swallowed the fly. Perhaps she'll die."


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
            current_animal = animals[i]
            previous_animal = animals[i - 1]
            line = f"She swallowed the {current_animal} to catch the {previous_animal}."
            
            if previous_animal == "spider":
                line = f"She swallowed the {current_animal} to catch the spider{SPIDER_SUFFIX}"
            
            result.append(line)
        
        result.append(FLY_ENDING)
    
    return result