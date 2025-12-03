RECOGNIZE = {
    "     |  |   ": '1',
    " _  _||_    ": '2',
    " _  _| _|   ": '3',
    "   |_|  |   ": '4',
    " _ |_  _|   ": '5',
    " _ |_ |_|   ": '6',
    " _   |  |   ": '7',
    " _ |_||_|   ": '8',
    " _ |_| _|   ": '9',
    " _ | ||_|   ": '0',
}


def convert(input_grid):
    if not input_grid or len(input_grid) % 4 != 0:
        raise ValueError("Invalid input grid")

    numbers = []
    for i in range(0, len(input_grid), 4):
        numbers.append(four_rows_to_numbers(input_grid[i:i + 4]))

    return ",".join(numbers)


def four_rows_to_numbers(rows):
    if any(not r or len(r) % 3 != 0 for r in rows):
        raise ValueError("Invalid row length")

    numbers = []
    row_len = len(rows[0])
    for i in range(0, row_len, 3):
        number = "".join(rows[j][i:i + 3] for j in range(4))
        numbers.append(RECOGNIZE.get(number, "?"))

    return "".join(numbers)