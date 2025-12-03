def binary_search(list_of_numbers, number):
    start, end = 0, len(list_of_numbers) - 1
    while start <= end:
        middle = start + (end - start) // 2
        if (current := list_of_numbers[middle]) < number:
            start = middle + 1
        elif current > number:
            end = middle - 1
        else:
            return middle
    raise ValueError(f"{number} not in list")