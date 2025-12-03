class ConnectGame:
    def __init__(self, board):
        self.board = [row.replace(" ", "") for row in board.splitlines()]
        self.rows = len(self.board)
        self.cols = len(self.board[0]) if self.rows > 0 else 0

    def get_winner(self):
        if self.is_winner("O"):
            return "O"
        if self.is_winner("X"):
            return "X"
        return ""

    def is_winner(self, player):
        if player == "O":
            board = self.board
            start_positions = [(0, c) for c in range(self.cols) if board[0][c] == player]
            target_row = self.rows - 1
        else:
            board = [[self.board[r][c] for r in range(self.rows)] for c in range(self.cols)]
            start_positions = [(0, r) for r in range(self.rows) if board[0][r] == player]
            target_row = self.cols - 1

        stack = start_positions
        visited = set(start_positions)

        while stack:
            r, c = stack.pop()
            if r == target_row:
                return True

            for dr, dc in [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < len(board) and 0 <= nc < len(board[0]) and board[nr][nc] == player and (nr, nc) not in visited:
                    stack.append((nr, nc))
                    visited.add((nr, nc))

        return False