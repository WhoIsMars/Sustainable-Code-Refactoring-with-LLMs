class ConnectGame:
    def __init__(self, board):
        self.board = [row.replace(" ", "") for row in board.splitlines()]
        self.transposed_board = list(map("".join, zip(*self.board)))

    def get_winner(self):
        if self.is_winner("O"):
            return "O"
        if self.is_winner("X"):
            return "X"
        return ""

    def is_winner(self, player):
        board = self.board if player == "O" else self.transposed_board
        positions = [(0, c) for c, s in enumerate(board[0]) if s == player]
        checked = set(positions)
        directions = [(-1, 1), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 0)]

        while positions:
            r, c = positions.pop()
            if r == len(board) - 1:
                return True

            for i, j in directions:
                r_, c_ = r + i, c + j
                if 0 <= r_ < len(board) and 0 <= c_ < len(board[0]) \
                        and board[r_][c_] == player and (r_, c_) not in checked:
                    positions.append((r_, c_))
                    checked.add((r_, c_))

        return False