def binary_search(list_of_numbers, number):
    start, end = 0, len(list_of_numbers) - 1
    while start <= end:
        middle = start + (end - start) // 2
        mid_val = list_of_numbers[middle]
        if number > mid_val:
            start = middle + 1
        elif number < mid_val:
            end = middle - 1
        else:
            return middle
    raise ValueError(f"{number} not in list")