def binary_search(list_of_numbers, number):
    start, end = 0, len(list_of_numbers) - 1
    while start <= end:
        middle = start + ((end - start) >> 1)
        middle_value = list_of_numbers[middle]
        if number > middle_value:
            start = middle + 1
        elif number < middle_value:
            end = middle - 1
        else:
            return middle
    raise ValueError(f"{number} not in list")