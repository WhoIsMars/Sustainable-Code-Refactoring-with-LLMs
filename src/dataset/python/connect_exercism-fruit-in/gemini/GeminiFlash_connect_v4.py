class ConnectGame:
    def __init__(self, board):
        self.board = tuple(row.replace(" ", "") for row in board.splitlines())
        self.rows = len(self.board)
        self.cols = len(self.board[0]) if self.rows > 0 else 0

    def get_winner(self):
        if self._has_path("O"):
            return "O"
        elif self._has_path("X"):
            return "X"
        else:
            return ""

    def _has_path(self, player):
        if player == "O":
            board = self.board
            start_positions = [(0, c) for c in range(self.cols) if self.board[0][c] == player]
            target_row = self.rows - 1
        else:
            board = tuple(tuple(self.board[r][c] for r in range(self.rows)) for c in range(self.cols))
            start_positions = [(0, r) for r in range(self.rows) if board[0][r] == player]
            target_row = self.cols - 1

        visited = set()
        stack = start_positions

        while stack:
            row, col = stack.pop()

            if row == target_row:
                return True

            for dr, dc in [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]:
                new_row, new_col = row + dr, col + dc

                if 0 <= new_row < len(board) and 0 <= new_col < len(board[0]) and \
                   board[new_row][new_col] == player and (new_row, new_col) not in visited:
                    stack.append((new_row, new_col))
                    visited.add((new_row, new_col))

        return False