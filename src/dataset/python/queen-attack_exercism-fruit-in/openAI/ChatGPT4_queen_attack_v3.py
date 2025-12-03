class Queen:
    def __init__(self, row, column):
        if not (0 <= row <= 7 and 0 <= column <= 7):
            raise ValueError(r".+")

        self.row = row
        self.col = column

    def can_attack(self, another_queen):
        if (self.row, self.col) == (another_queen.row, another_queen.col):
            raise ValueError(r".+")

        row_diff = abs(self.row - another_queen.row)
        col_diff = abs(self.col - another_queen.col)
        return self.row == another_queen.row or self.col == another_queen.col or row_diff == col_diff