def find(search_list, value):
    l = 0
    r = len(search_list)

    while l < r:
        m = (l + r) >> 1  # Use bitwise shift for faster division by 2

        if search_list[m] < value:
            l = m + 1
        elif search_list[m] > value:
            r = m
        else:
            return m

    raise ValueError(r".+")