def square_of_sum(num):
    """Square of sum of numbers less than or equal to [num]"""
    return (num * (num + 1) // 2) ** 2

def sum_of_squares(num):
    """Sum of squares of numbers less than or equal to [num]"""
    return num * (num + 1) * (2 * num + 1) // 6

def difference(num):
    """Difference between the square_of_sum and sum_of_squares"""
    return (num * (num + 1) * (num - 1) * (3 * num + 2)) // 12