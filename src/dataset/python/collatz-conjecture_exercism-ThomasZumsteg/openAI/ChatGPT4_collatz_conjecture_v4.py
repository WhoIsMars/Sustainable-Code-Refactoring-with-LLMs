def collatz_steps(number):
    if number <= 0:
        raise ValueError(f"Number must be greater than 0: collatz_steps({number})")
    steps = 0
    while number != 1:
        number = number >> 1 if number & 1 == 0 else 3 * number + 1
        steps += 1
    return steps