class ConnectGame:
    def __init__(self, board):
        self.board = [row.replace(" ", "") for row in board.splitlines()]
        self.rows = len(self.board)
        self.cols = len(self.board[0]) if self.rows > 0 else 0

    def get_winner(self):
        if self.is_winner("O"):
            return "O"
        elif self.is_winner("X"):
            return "X"
        else:
            return ""

    def is_winner(self, player):
        if player == "O":
            board = self.board
            rows = self.rows
            cols = self.cols
            start_positions = [(0, c) for c in range(cols) if self.board[0][c] == player]
        else:
            board = list(zip(*self.board))
            rows = self.cols
            cols = self.rows
            start_positions = [(0, r) for r in range(rows) if board[0][r] == player]

        visited = set()
        queue = start_positions

        while queue:
            r, c = queue.pop(0)

            if r == rows - 1:
                return True

            for dr, dc in [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]:
                new_r = r + dr
                new_c = c + dc

                if 0 <= new_r < rows and 0 <= new_c < cols and board[new_r][new_c] == player and (new_r, new_c) not in visited:
                    queue.append((new_r, new_c))
                    visited.add((new_r, new_c))

        return False