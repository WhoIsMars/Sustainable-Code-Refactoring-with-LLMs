def recite(start, take=1):
    sing = []
    for i in range(take):
        n = start - i
        sing.extend(verse(n))
    return sing[:-1]


def verse(n):
    b = bottle(n)
    b_lower = b.lower()
    t = take_down(n)
    next_bottle = bottle((n + 99) % 100).lower()

    return [
        f"{b} of beer on the wall, {b_lower} of beer.",
        f"{t}, {next_bottle} of beer on the wall.",
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