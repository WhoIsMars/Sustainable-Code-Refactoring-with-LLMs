"""Fills in number on a minesweeper board"""

from re import compile

def validate_and_format(func):
    """Finds bad boards and formats function return"""
    def minesweeper(minefield):
        """Finds bad boards and formats function returns"""
        if not minefield:
            raise ValueError
        
        width = len(minefield[0])
        if width < 3:
            raise ValueError
            
        row_regex = compile(r'^\|[* ]{%d}\|$' % (width-2))
        cap_regex = compile(r'^\+-{%d}\+$' % (width-2))
        
        if not cap_regex.match(minefield[0]) or not cap_regex.match(minefield[-1]):
            raise ValueError
            
        for row in minefield[1:-1]:
            if not row_regex.match(row):
                raise ValueError
        
        minefield = [list(row) for row in minefield]
        return [''.join(row) for row in func(minefield)]
    return minesweeper

@validate_and_format
def board(minefield):
    """Fills in numbers on a minesweeper board"""
    mines = []
    for i in range(1, len(minefield) - 1):
        for j in range(1, len(minefield[i]) - 1):
            if minefield[i][j] == "*":
                mines.append((i, j))
    
    for row, col in mines:
        update(minefield, row, col)
    
    return minefield

def update(field, row, col):
    """Updates a set of 9 cells"""
    max_row = len(field) - 1
    max_col = len(field[0]) - 1
    
    for m in range(max(0, row-1), min(max_row + 1, row+2)):
        for n in range(max(0, col-1), min(max_col + 1, col+2)):
            cell = field[m][n]
            if cell == ' ':
                field[m][n] = '1'
            elif cell.isdigit():
                field[m][n] = str(int(cell) + 1)