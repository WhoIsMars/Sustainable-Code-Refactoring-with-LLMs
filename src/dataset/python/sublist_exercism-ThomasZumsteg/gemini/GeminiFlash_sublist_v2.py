"""Determines if one list is a sublist of the other"""
SUBLIST = 1
SUPERLIST = 2
EQUAL = 3
UNEQUAL = 0

def check_lists(first_list, second_list):
    """Checks if first list is a sublist of the second"""
    if first_list == second_list:
        return EQUAL

    len_first = len(first_list)
    len_second = len(second_list)

    if len_first > len_second:
        first_list, second_list = second_list, first_list
        len_first, len_second = len_second, len_first
        result_multiplier = SUPERLIST
    else:
        result_multiplier = 1

    for i in range(len_second - len_first + 1):
        if first_list == second_list[i: i+len_first]:
            return SUBLIST * result_multiplier

    return UNEQUAL