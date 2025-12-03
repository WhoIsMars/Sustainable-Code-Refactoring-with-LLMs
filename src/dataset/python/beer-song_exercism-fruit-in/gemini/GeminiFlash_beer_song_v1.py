def recite(start, take=1):
    sing = []
    for i in range(take):
        n = start - i
        sing.append(f"{bottle(n)} of beer on the wall, {bottle(n).lower()} of beer.")
        sing.append(f"{take_down(n)}, {bottle((n + 99) % 100).lower()} of beer on the wall.")
        sing.append("")
    return sing[:-1]


def verse(n):
    return [
        f"{bottle(n)} of beer on the wall, {bottle(n).lower()} of beer.",
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