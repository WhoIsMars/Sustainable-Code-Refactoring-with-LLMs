def is_armstrong(number):
    str_num = str(number)
    num_digits = len(str_num)
    total = 0
    for digit_char in str_num:
        total += int(digit_char) ** num_digits
    return total == number