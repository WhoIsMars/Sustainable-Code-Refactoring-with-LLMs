"""Replys to statements as a lackadaisical teenager would"""

def hey(what):
    """Replys to statements as a lackadaisical teenager would"""
    stripped_what = what.strip()
    if not stripped_what:
        return 'Fine. Be that way!'
    elif stripped_what.isupper():
        return 'Whoa, chill out!'
    elif stripped_what.endswith('?'):
        return 'Sure.'
    else:
        return 'Whatever.'