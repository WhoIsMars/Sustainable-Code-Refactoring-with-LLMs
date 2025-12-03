"""Recites 'This is the House that Jack Built'"""

def rhyme():
    """Recites the entire rhyme"""
    return "\n\n".join(verse(n) for n in range(12))

def verse(v):
    """Recites a verse"""
    return f"This is {''.join(VERSES[-v-1:])}"

VERSES = [
    "the house that Jack built.",
    "the malt\nthat lay in ",
    "the rat\nthat ate ",
    "the cat\nthat killed ",
    "the dog\nthat worried ",
    "the cow with the crumpled horn\nthat tossed ",
    "the maiden all forlorn\nthat milked ",
    "the man all tattered and torn\nthat kissed ",
    "the priest all shaven and shorn\nthat married ",
    "the rooster that crowed in the morn\nthat woke ",
    "the farmer sowing his corn\nthat kept ",
    "the horse and the hound and the horn\nthat belonged to "
]