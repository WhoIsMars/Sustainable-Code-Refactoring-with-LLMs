def spiral(size):
    result = [[0] * size for _ in range(size)]
    num = 1
    start_row, end_row = 0, size - 1
    start_col, end_col = 0, size - 1

    while num <= size * size:
        # Traverse right
        for i in range(start_col, end_col + 1):
            result[start_row][i] = num
            num += 1
        start_row += 1

        # Traverse down
        for i in range(start_row, end_row + 1):
            result[i][end_col] = num
            num += 1
        end_col -= 1

        # Traverse left
        if start_row <= end_row:
            for i in range(end_col, start_col - 1, -1):
                result[end_row][i] = num
                num += 1
            end_row -= 1

        # Traverse up
        if start_col <= end_col:
            for i in range(end_row, start_row - 1, -1):
                result[i][start_col] = num
                num += 1
            start_col += 1

    return result