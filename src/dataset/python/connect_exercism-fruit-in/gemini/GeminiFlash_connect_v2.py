class ConnectGame:
    def __init__(self, board):
        self.board = tuple(row.replace(" ", "") for row in board.splitlines())
        self.rows = len(self.board)
        self.cols = len(self.board[0]) if self.rows > 0 else 0

    def get_winner(self):
        winner = self._check_winner("O")
        if winner:
            return "O"
        winner = self._check_winner("X")
        if winner:
            return "X"
        return ""

    def _check_winner(self, player):
        if player == "O":
            board = self.board
            rows = self.rows
            cols = self.cols
            target_row = rows - 1
            start_positions = [(0, c) for c in range(cols) if board[0][c] == player]
            
        else:  # player == "X"
            board = tuple("".join(self.board[r][c] for r in range(self.rows)) for c in range(self.cols))
            rows = self.cols
            cols = self.rows
            target_row = rows - 1
            start_positions = [(0, c) for c in range(cols) if board[0][c] == player]

        visited = set()
        
        def explore(r, c):
            if r == target_row:
                return True
            
            visited.add((r, c))
            
            for dr, dc in [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and board[nr][nc] == player and (nr, nc) not in visited:
                    if explore(nr, nc):
                        return True
            return False

        for start_r, start_c in start_positions:
            if explore(start_r, start_c):
                return True
        
        return False