def recite(start, take=1):
    if take <= 0:
        return []
    
    result = []
    for i in range(take):
        verse_num = start - i
        bottle_text = _bottle(verse_num)
        bottle_lower = bottle_text.lower()
        next_bottle = _bottle((verse_num + 99) % 100).lower()
        take_down_text = _take_down(verse_num)
        
        result.extend([
            f"{bottle_text} of beer on the wall, {bottle_lower} of beer.",
            f"{take_down_text}, {next_bottle} of beer on the wall.",
            ""
        ])
    
    return result[:-1]


def verse(n):
    bottle_text = _bottle(n)
    bottle_lower = bottle_text.lower()
    next_bottle = _bottle((n + 99) % 100).lower()
    take_down_text = _take_down(n)
    
    return [
        f"{bottle_text} of beer on the wall, {bottle_lower} of beer.",
        f"{take_down_text}, {next_bottle} of beer on the wall.",
        ""
    ]


def take_down(n):
    return _take_down(n)


def bottle(n):
    return _bottle(n)


def _take_down(n):
    if n == 0:
        return "Go to the store and buy some more"
    elif n == 1:
        return "Take it down and pass it around"
    else:
        return "Take one down and pass it around"


def _bottle(n):
    if n == 0:
        return "No more bottles"
    elif n == 1:
        return "1 bottle"
    else:
        return f"{n} bottles"