class Queen:
    def __init__(self, row, column):
        if not (0 <= row <= 7 and 0 <= column <= 7):
            raise ValueError("Position out of bounds.")
        self.row = row
        self.col = column

    def can_attack(self, another_queen):
        if (self.row, self.col) == (another_queen.row, another_queen.col):
            raise ValueError("Queens cannot occupy the same position.")
        row_diff = self.row - another_queen.row
        col_diff = self.col - another_queen.col
        return row_diff == 0 or col_diff == 0 or abs(row_diff) == abs(col_diff)