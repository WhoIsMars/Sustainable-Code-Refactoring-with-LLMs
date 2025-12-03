"""Fills in number on a minesweeper board"""

from re import compile

def validate_and_format(func):
    """Finds bad boards and formats function return"""
    def minesweeper(minefield):
        """Finds bad boards and formats function returns"""
        width = len(minefield[0])
        row_regex = compile(r'^\|[* ]{%d}\|$' %(width-2))
        cap_regex = compile(r'^\+-{%d}\+$' %(width-2))
        if not all(row_regex.match(row) for row in minefield[1:-1]) or \
           not cap_regex.match(minefield[0]) or \
           not cap_regex.match(minefield[-1]):
            raise ValueError
        minefield = [list(row) for row in minefield]
        return [''.join(row) for row in func(minefield)]
    return minesweeper

@validate_and_format
def board(minefield):
    """Fills in numbers on a minesweeper board"""
    height = len(minefield)
    width = len(minefield[0])
    
    for i in range(1, height - 1):
        row = minefield[i]
        for j in range(1, width - 1):
            if row[j] == "*":
                # Inline update logic to avoid function call overhead
                for m in range(max(0, i-1), min(height, i+2)):
                    field_row = minefield[m]
                    for n in range(max(0, j-1), min(width, j+2)):
                        cell = field_row[n]
                        if cell == ' ':
                            field_row[n] = '1'
                        elif cell.isdigit():
                            field_row[n] = str(int(cell) + 1)
    return minefield

def update(field, row, col):
    """Updates a set of 9 cells"""
    # Uses pass by reference (sort of)
    for m in range(row-1, row+2):
        for n in range(col-1, col+2):
            if field[m][n] == ' ':
                field[m][n] = '1'
            elif field[m][n].isdigit():
                field[m][n] = str(int(field[m][n]) + 1)