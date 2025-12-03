def find(search_list, value):
    l, r = 0, len(search_list) - 1

    while l <= r:
        m = l + (r - l) // 2

        if search_list[m] < value:
            l = m + 1
        elif search_list[m] > value:
            r = m - 1
        else:
            return m

    raise ValueError("Value not found")