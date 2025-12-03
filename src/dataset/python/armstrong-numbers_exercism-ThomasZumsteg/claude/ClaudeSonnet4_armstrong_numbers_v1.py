def is_armstrong(number):
    str_num = str(number)
    num_digits = len(str_num)
    return sum(int(d)**num_digits for d in str_num) == number