def recite(start, take=1):
    if take <= 0:
        return []
    
    result = []
    for i in range(take):
        n = start - i
        bottle_n = _bottle(n)
        bottle_n_lower = bottle_n.lower()
        next_n = (n + 99) % 100
        bottle_next_lower = _bottle(next_n).lower()
        take_down_text = _take_down(n)
        
        result.extend([
            f"{bottle_n} of beer on the wall, {bottle_n_lower} of beer.",
            f"{take_down_text}, {bottle_next_lower} of beer on the wall.",
            ""
        ])
    
    return result[:-1]


def verse(n):
    bottle_n = _bottle(n)
    bottle_n_lower = bottle_n.lower()
    next_n = (n + 99) % 100
    bottle_next_lower = _bottle(next_n).lower()
    take_down_text = _take_down(n)
    
    return [
        f"{bottle_n} of beer on the wall, {bottle_n_lower} of beer.",
        f"{take_down_text}, {bottle_next_lower} of beer on the wall.",
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