"""Queen chess moves"""

def validate(func):
    """Ensures valid chess positions"""
    def chess_checker(black, white):
        """Ensures valid chess positions"""
        if not (0 <= black[0] <= 7 and 0 <= black[1] <= 7 and 0 <= white[0] <= 7 and 0 <= white[1] <= 7) or black == white:
            raise ValueError
        return func(black, white)
    return chess_checker

@validate
def board(white, black):
    """Prints a board with the queens locations"""
    chess = ["_" * 8 for _ in range(8)]
    white_row = list(chess[white[0]])
    white_row[white[1]] = "W"
    chess[white[0]] = "".join(white_row)

    black_row = list(chess[black[0]])
    black_row[black[1]] = "B"
    chess[black[0]] = "".join(black_row)
    
    return chess

@validate
def can_attack(black, white):
    """Checks if the two queens can attack eachother"""
    return black[0] == white[0] or black[1] == white[1] or abs(black[0] - white[0]) == abs(black[1] - white[1])