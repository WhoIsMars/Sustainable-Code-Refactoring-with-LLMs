def is_armstrong(number):
    digits = str(number)
    power = len(digits)
    return sum(int(d)**power for d in digits) == number