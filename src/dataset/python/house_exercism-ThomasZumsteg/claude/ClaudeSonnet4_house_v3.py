"""Recites 'This is the House that Jack Built'"""

def rhyme():
    """Recites the entire rhyme"""
    verses = []
    accumulated = "the house that Jack built."
    
    for i in range(12):
        verses.append("This is " + accumulated)
        if i < 11:
            accumulated = VERSES[10-i] + accumulated
    
    return "\n\n".join(verses)

def verse(v):
    """Recites a verse"""
    if v == 0:
        return "This is the house that Jack built."
    
    result = "This is "
    for i in range(11-v, 12):
        result += VERSES[i]
    
    return result

VERSES = (
    "the horse and the hound and the horn\nthat belonged to ",
    "the farmer sowing his corn\nthat kept ",
    "the rooster that crowed in the morn\nthat woke ",
    "the priest all shaven and shorn\nthat married ",
    "the man all tattered and torn\nthat kissed ",
    "the maiden all forlorn\nthat milked ",
    "the cow with the crumpled horn\nthat tossed ",
    "the dog\nthat worried ",
    "the cat\nthat killed ",
    "the rat\nthat ate ",
    "the malt\nthat lay in ",
    "the house that Jack built."
)