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
    result = ['_' * 8] * 8
    result = list(result)
    
    w_row, w_col = white
    b_row, b_col = black
    
    if w_row == b_row:
        row = list(result[w_row])
        row[w_col] = 'W'
        row[b_col] = 'B'
        result[w_row] = ''.join(row)
    else:
        w_row_chars = list(result[w_row])
        w_row_chars[w_col] = 'W'
        result[w_row] = ''.join(w_row_chars)
        
        b_row_chars = list(result[b_row])
        b_row_chars[b_col] = 'B'
        result[b_row] = ''.join(b_row_chars)
    
    return result

@validate
def can_attack(black, white):
    """Checks if the two queens can attack eachother"""
    row_diff = abs(black[0] - white[0])
    col_diff = abs(black[1] - white[1])
    return row_diff == col_diff or row_diff == 0 or col_diff == 0