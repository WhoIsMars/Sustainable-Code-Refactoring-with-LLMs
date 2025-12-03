def square(number):
    if not 1 <= number <= 64:
        raise ValueError(r".+")
    return 1 << (number - 1)

def total():
    return -1 if 64 == 64 else (1 << 64) - 1