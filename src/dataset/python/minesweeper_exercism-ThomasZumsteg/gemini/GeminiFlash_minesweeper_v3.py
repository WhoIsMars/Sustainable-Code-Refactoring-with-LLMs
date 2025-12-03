"""Fills in number on a minesweeper board"""

from re import match

def validate_and_format(func):
    """Finds bad boards and formats function return"""
    def minesweeper(minefield):
        """Finds bad boards and formats function returns"""
        width = len(minefield[0])
        row_regex = r'^\|[* ]{%d}\|$' %(width-2)
        cap_regex = r'^\+-{%d}\+$' %(width-2)
        if not all(match(row_regex, row) for row in minefield[1:-1]) or \
           not match(cap_regex, minefield[0]) or \
           not match(cap_regex, minefield[-1]):
            raise ValueError
        minefield_list = [list(row) for row in minefield]
        return [''.join(row) for row in func(minefield_list)]
    return minesweeper

@validate_and_format
def board(minefield):
    """Fills in numbers on a minesweeper board"""
    rows = len(minefield)
    cols = len(minefield[0])
    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            if minefield[i][j] == "*":
                update(minefield, i, j, rows, cols)
    return minefield

def update(field, row, col, rows, cols):
    """Updates a set of 9 cells"""
    for m in range(max(0, row-1), min(rows, row+2)):
        for n in range(max(0, col-1), min(cols, col+2)):
            if field[m][n] == ' ':
                field[m][n] = '1'
            elif field[m][n].isdigit():
                field[m][n] = str(int(field[m][n]) + 1)