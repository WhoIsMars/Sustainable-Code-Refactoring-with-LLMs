"""Determines if one list is a sublist of the other"""
SUBLIST = 1
SUPERLIST = 2
EQUAL = 3
UNEQUAL = 0

def swapper(func):
    """Wrapper that ensures the first argument is smaller than the second"""
    def swap(first, second):
        if first == second:
            return EQUAL
        if len(first) > len(second):
            return SUPERLIST * func(second, first)
        return func(first, second)
    return swap

@swapper
def check_lists(small_list, big_list):
    """Checks if first list is a sublist of the second"""
    small_len = len(small_list)
    if small_len == 0:
        return SUBLIST
    big_len = len(big_list)
    for i in range(big_len - small_len + 1):
        if big_list[i] == small_list[0] and big_list[i:i + small_len] == small_list:
            return SUBLIST
    return UNEQUAL