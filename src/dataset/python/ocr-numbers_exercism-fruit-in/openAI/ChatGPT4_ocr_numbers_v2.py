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
        raise ValueError(r".+")

    return ",".join(
        four_rows_to_numbers(input_grid[i:i + 4])
        for i in range(0, len(input_grid), 4)
    )


def four_rows_to_numbers(rows):
    if len(rows) != 4 or any(len(r) % 3 != 0 for r in rows):
        raise ValueError(r".+")

    return "".join(
        RECOGNIZE.get(
            "".join(row[i:i + 3] for row in rows), "?"
        )
        for i in range(0, len(rows[0]), 3)
    )