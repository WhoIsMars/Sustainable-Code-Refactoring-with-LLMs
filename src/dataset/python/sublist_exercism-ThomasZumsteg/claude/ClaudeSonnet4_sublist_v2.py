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
    if not small_list:
        return SUBLIST
    
    small_len = len(small_list)
    big_len = len(big_list)
    
    if small_len > big_len:
        return UNEQUAL
    
    first_elem = small_list[0]
    
    for i in range(big_len - small_len + 1):
        if big_list[i] == first_elem:
            match = True
            for j in range(1, small_len):
                if big_list[i + j] != small_list[j]:
                    match = False
                    break
            if match:
                return SUBLIST
    
    return UNEQUAL