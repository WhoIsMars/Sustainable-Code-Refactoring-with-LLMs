def recite(start, take=1):
    if take == 0:
        return []
    
    result = []
    for i in range(take):
        n = start - i
        bottle_text = bottle(n)
        bottle_lower = bottle_text.lower()
        next_bottle = bottle((n + 99) % 100).lower()
        
        result.extend([
            f"{bottle_text} of beer on the wall, {bottle_lower} of beer.",
            f"{take_down(n)}, {next_bottle} of beer on the wall.",
            ""
        ])
    
    return result[:-1]


def verse(n):
    bottle_text = bottle(n)
    bottle_lower = bottle_text.lower()
    next_bottle = bottle((n + 99) % 100).lower()
    
    return [
        f"{bottle_text} of beer on the wall, {bottle_lower} of beer.",
        f"{take_down(n)}, {next_bottle} of beer on the wall.",
        "",
    ]


def take_down(n):
    if n == 0:
        return "Go to the store and buy some more"
    elif n == 1:
        return "Take it down and pass it around"
    else:
        return "Take one down and pass it around"


def bottle(n):
    if n == 0:
        return "No more bottles"
    elif n == 1:
        return "1 bottle"
    else:
        return f"{n} bottles"