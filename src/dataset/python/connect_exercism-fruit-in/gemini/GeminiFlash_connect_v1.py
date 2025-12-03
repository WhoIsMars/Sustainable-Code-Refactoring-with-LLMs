class ConnectGame:
    def __init__(self, board):
        self.board = [row.replace(" ", "") for row in board.splitlines()]
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
            start_positions = [(0, c) for c in range(self.cols) if self.board[0][c] == player]
            target_row = self.rows - 1
        else:
            board = list(zip(*self.board))  # Transpose the board efficiently
            start_positions = [(0, r) for r in range(self.rows) if board[0][r] == player]
            target_row = self.cols - 1

        visited = set()

        def explore(row, col):
            if row == target_row:
                return True

            visited.add((row, col))
            for dr, dc in [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]:
                new_row, new_col = row + dr, col + dc
                if 0 <= new_row < len(board) and 0 <= new_col < len(board[0]) and \
                   board[new_row][new_col] == player and (new_row, new_col) not in visited:
                    if explore(new_row, new_col):
                        return True
            return False

        for start_row, start_col in start_positions:
            if explore(start_row, start_col):
                return True

        return False