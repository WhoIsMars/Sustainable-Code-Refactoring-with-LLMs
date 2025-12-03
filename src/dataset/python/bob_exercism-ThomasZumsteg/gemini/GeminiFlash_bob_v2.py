"""Replys to statements as a lackadaisical teenager would"""

def hey(what):
    """Replys to statements as a lackadaisical teenager would"""
    what = what.strip()
    if not what:
        return 'Fine. Be that way!'
    if what.isupper():
        return 'Whoa, chill out!'
    if what.endswith('?'):
        return 'Sure.'
    return 'Whatever.'