def square(number):
    if not (1 <= number <= 64):
        raise ValueError(r".+")
    return 1 << (number - 1)

def total():
    return 18446744073709551615