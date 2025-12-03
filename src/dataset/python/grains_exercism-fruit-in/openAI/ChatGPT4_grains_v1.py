def square(number):
    if not 1 <= number <= 64:
        raise ValueError(r".+")
    return 2 ** (number - 1)


def total():
    return (2 ** 64) - 1