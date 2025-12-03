def recite(start, take=1):
    if take == 0:
        return []
    
    sing = []
    for i in range(take):
        current = start - i
        sing.extend([
            f"{bottle(current)} of beer on the wall, {bottle(current).lower()} of beer.",
            f"{take_down(current)}, {bottle((current + 99) % 100).lower()} of beer on the wall.",
            ""
        ])
    
    return sing[:-1]


def verse(n):
    bottle_text = bottle(n)
    return [
        f"{bottle_text} of beer on the wall, {bottle_text.lower()} of beer.",
        f"{take_down(n)}, {bottle((n + 99) % 100).lower()} of beer on the wall.",
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