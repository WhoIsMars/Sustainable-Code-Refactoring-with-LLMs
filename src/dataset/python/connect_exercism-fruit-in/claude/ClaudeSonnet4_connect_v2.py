class ConnectGame:
    def __init__(self, board):
        self.board = [row.replace(" ", "") for row in board.splitlines()]
        self.rows = len(self.board)
        self.cols = len(self.board[0])

    def get_winner(self):
        if self.is_winner("O"):
            return "O"
        elif self.is_winner("X"):
            return "X"
        else:
            return ""

    def is_winner(self, player):
        if player == "X":
            # Transpose board for X player
            board = [[self.board[r][c] for r in range(self.rows)] for c in range(self.cols)]
            rows, cols = self.cols, self.rows
        else:
            board = self.board
            rows, cols = self.rows, self.cols
        
        # Find starting positions in first row
        positions = []
        checked = set()
        
        for c in range(cols):
            if board[0][c] == player:
                positions.append((0, c))
                checked.add((0, c))
        
        # BFS traversal
        directions = [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]
        
        while positions:
            r, c = positions.pop()
            
            if r == rows - 1:
                return True
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                if (0 <= nr < rows and 0 <= nc < cols and 
                    board[nr][nc] == player and (nr, nc) not in checked):
                    positions.append((nr, nc))
                    checked.add((nr, nc))
        
        return False