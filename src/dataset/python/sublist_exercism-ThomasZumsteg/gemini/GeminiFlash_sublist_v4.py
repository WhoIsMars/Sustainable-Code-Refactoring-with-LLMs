"""Determines if one list is a sublist of the other"""
SUBLIST = 1
SUPERLIST = 2
EQUAL = 3
UNEQUAL = 0

def swapper(func):
    """Wrapper that ensures the first argument is smaller then the seconds"""
    def swap(first, second):
        """swaps first and second argument if the second is smaller"""
        if first == second:
            return EQUAL
        if len(first) > len(second):
            return SUPERLIST * func(second, first)
        else:
            return func(first, second)
    return swap

@swapper
def check_lists(small_list, big_list):
    """Checks if first list is a sublist of the seconds"""
    len_small = len(small_list)
    len_big = len(big_list)

    for i in range(len_big - len_small + 1):
        if small_list == big_list[i:i + len_small]:
            return SUBLIST
    return UNEQUAL