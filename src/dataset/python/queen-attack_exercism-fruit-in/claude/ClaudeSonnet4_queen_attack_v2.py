class Queen:
    __slots__ = ('row', 'col')
    
    def __init__(self, row, column):
        if not (0 <= row <= 7) or not (0 <= column <= 7):
            raise ValueError(r".+")

        self.row = row
        self.col = column

    def can_attack(self, another_queen):
        if self.row == another_queen.row and self.col == another_queen.col:
            raise ValueError(r".+")

        row_diff = self.row - another_queen.row
        col_diff = self.col - another_queen.col
        
        return row_diff == 0 or col_diff == 0 or abs(row_diff) == abs(col_diff)