def is_armstrong(number):
    if number < 0:
        return False
    
    str_num = str(number)
    num_digits = len(str_num)
    
    total = 0
    for digit_char in str_num:
        digit = ord(digit_char) - 48
        total += digit ** num_digits
        if total > number:
            return False
    
    return total == number