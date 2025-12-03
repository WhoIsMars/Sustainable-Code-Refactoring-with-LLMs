def collatz_steps(number):
    if number <= 0:
        raise ValueError(
                "Number must be greater then 0: collatz_steps({})".format(number))
    step = 0
    while number != 1:
        if number & 1:
            number = 3 * number + 1
        else:
            number >>= 1
        step += 1
    return step