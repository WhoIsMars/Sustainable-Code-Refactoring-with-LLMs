class ConnectGame:
    def __init__(self, board):
        self.board = [row.replace(" ", "") for row in board.splitlines()]
        self.rows = len(self.board)
        self.cols = len(self.board[0]) if self.board else 0

    def get_winner(self):
        if self.is_winner("O"):
            return "O"
        elif self.is_winner("X"):
            return "X"
        else:
            return ""

    def is_winner(self, player):
        if player == "X":
            board = [[self.board[r][c] for r in range(self.rows)] for c in range(self.cols)]
            rows, cols = self.cols, self.rows
        else:
            board = self.board
            rows, cols = self.rows, self.cols
        
        positions = []
        checked = set()
        
        for c in range(cols):
            if board[0][c] == player:
                pos = (0, c)
                positions.append(pos)
                checked.add(pos)
        
        directions = [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]
        
        while positions:
            r, c = positions.pop()
            
            if r == rows - 1:
                return True
            
            for i, j in directions:
                r_ = r + i
                c_ = c + j
                
                if 0 <= r_ < rows and 0 <= c_ < cols and board[r_][c_] == player:
                    pos = (r_, c_)
                    if pos not in checked:
                        positions.append(pos)
                        checked.add(pos)
        
        return False