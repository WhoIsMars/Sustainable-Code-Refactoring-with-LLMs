def is_armstrong(number):
    num_str = str(number)
    power = len(num_str)
    return sum(int(d)**power for d in num_str) == number