def collatz_steps(number):
    if number <= 0:
        raise ValueError(f"Number must be greater than 0: collatz_steps({number})")
    step = 0
    while number != 1:
        number = number // 2 if number % 2 == 0 else 3 * number + 1
        step += 1
    return step