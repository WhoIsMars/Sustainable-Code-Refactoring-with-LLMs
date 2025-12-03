"""Queen chess moves"""

def validate(func):
    """Ensures valid chess positions"""
    def chess_checker(black, white):
        """Ensures valid chess positions"""
        if (black[0] | black[1] | white[0] | white[1]) & ~7 or black == white:
            raise ValueError
        return func(black, white)
    return chess_checker

@validate
def board(white, black):
    """Prints a board with the queens locations"""
    chess = [['_'] * 8 for _ in range(8)]
    chess[white[0]][white[1]] = 'W'
    chess[black[0]][black[1]] = 'B'
    return [''.join(row) for row in chess]

@validate
def can_attack(black, white):
    """Checks if the two queens can attack eachother"""
    row_diff = abs(black[0] - white[0])
    col_diff = abs(black[1] - white[1])
    return row_diff == col_diff or row_diff == 0 or col_diff == 0