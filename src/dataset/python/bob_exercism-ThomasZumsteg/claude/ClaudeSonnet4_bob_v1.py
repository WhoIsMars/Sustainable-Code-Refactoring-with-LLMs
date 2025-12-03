"""Replys to statements as a lackadaisical teenager would"""

def hey(what):
    """Replys to statements as a lackadaisical teenager would"""
    what = what.strip()
    if not what:
        return 'Fine. Be that way!'
    elif what.isupper():
        return 'Whoa, chill out!'
    elif what.endswith('?'):
        return 'Sure.'
    else:
        return 'Whatever.'