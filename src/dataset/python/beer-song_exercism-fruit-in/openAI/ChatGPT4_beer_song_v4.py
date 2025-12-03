def recite(start, take=1):
    return [
        line
        for i in range(take)
        for line in verse(start - i)[:-1]
    ]


def verse(n):
    b = bottle(n)
    next_b = bottle((n + 99) % 100).lower()
    return [
        f"{b} of beer on the wall, {b.lower()} of beer.",
        f"{take_down(n)}, {next_b} of beer on the wall.",
        "",
    ]


def take_down(n):
    return (
        "Go to the store and buy some more" if n == 0 else
        "Take it down and pass it around" if n == 1 else
        "Take one down and pass it around"
    )


def bottle(n):
    return (
        "No more bottles" if n == 0 else
        "1 bottle" if n == 1 else
        f"{n} bottles"
    )