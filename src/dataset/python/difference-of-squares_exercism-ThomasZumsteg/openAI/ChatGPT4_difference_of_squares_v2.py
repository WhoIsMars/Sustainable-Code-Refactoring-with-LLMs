def square_of_sum(num):
    """Square of sum of numbers less than or equal to [num]"""
    sum_num = num * (num + 1) // 2
    return sum_num * sum_num

def sum_of_squares(num):
    """Sum of squares of numbers less than or equal to [num]"""
    return num * (num + 1) * (2 * num + 1) // 6

def difference(num):
    """Difference between the square_of_sum and sum_of_squares"""
    sum_num = num * (num + 1) // 2
    return sum_num * sum_num - num * (num + 1) * (2 * num + 1) // 6