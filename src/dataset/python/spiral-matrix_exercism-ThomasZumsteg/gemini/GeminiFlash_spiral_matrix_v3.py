def spiral(size):
    result = [[0] * size for _ in range(size)]
    num = 1
    start_row, end_row = 0, size - 1
    start_col, end_col = 0, size - 1

    while num <= size * size:
        for i in range(start_col, end_col + 1):
            if result[start_row][i] == 0:
                result[start_row][i] = num
                num += 1
        start_row += 1

        for i in range(start_row, end_row + 1):
            if result[i][end_col] == 0:
                result[i][end_col] = num
                num += 1
        end_col -= 1

        for i in range(end_col, start_col - 1, -1):
            if result[end_row][i] == 0:
                result[end_row][i] = num
                num += 1
        end_row -= 1

        for i in range(end_row, start_row - 1, -1):
            if result[i][start_col] == 0:
                result[i][start_col] = num
                num += 1
        start_col += 1

    return result