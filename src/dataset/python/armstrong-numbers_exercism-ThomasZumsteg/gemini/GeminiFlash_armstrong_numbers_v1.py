def is_armstrong(number):
    num_str = str(number)
    power = len(num_str)
    total = 0
    for digit in num_str:
        total += int(digit)**power
        if total > number:
            return False
    return total == number