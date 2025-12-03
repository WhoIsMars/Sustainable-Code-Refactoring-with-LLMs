def recite(start, take=1):
    sing = []
    for i in range(take):
        n = start - i
        sing.extend(verse(n))
    return sing[:-1]


def verse(n):
    bottle_str = bottle(n)
    bottle_lower = bottle_str.lower()
    take_down_str = take_down(n)
    next_bottle_num = (n + 99) % 100
    next_bottle_str = bottle(next_bottle_num).lower()

    return [
        f"{bottle_str} of beer on the wall, {bottle_lower} of beer.",
        f"{take_down_str}, {next_bottle_str} of beer on the wall.",
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