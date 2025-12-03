"""Recites 'This is the House that Jack Built'"""

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

_CACHED_VERSES = tuple("This is " + "".join(VERSES[-i-1:]) for i in range(12))

def rhyme():
    """Recites the entire rhyme"""
    return "\n\n".join(_CACHED_VERSES)

def verse(v):
    """Recites a verse"""
    return _CACHED_VERSES[v]