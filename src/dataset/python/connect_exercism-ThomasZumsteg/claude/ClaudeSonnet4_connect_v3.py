class ConnectGame:
    def __init__(self, board):
        self._board = [line.split() for line in board.splitlines()]
        self._height = len(self._board)
        self._width = len(self._board[0]) if self._board else 0
        
        self._players = {
            'X': (
                frozenset((0, r) for r in range(self._height)),
                frozenset((self._width - 1, r) for r in range(self._height))
            ),
            'O': (
                frozenset((c, 0) for c in range(self._width)),
                frozenset((c, self._height - 1) for c in range(self._width))
            )
        }
        
        self._directions = ((0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1))

    def get_winner(self):
        for player in self._players:
            if self._find_path(player):
                return player 
        return ''

    def _find_path(self, player):
        start, end = self._players[player]
        queue = list(start)
        seen = set()
        
        while queue:
            x, y = queue.pop()
            if (x, y) in seen:
                continue
            seen.add((x, y))
            
            if not (0 <= y < self._height and 0 <= x < self._width) or \
                    self._board[y][x] != player:
                continue
                
            if (x, y) in end:
                return True
                
            for dx, dy in self._directions:
                new_x, new_y = x + dx, y + dy
                if (new_x, new_y) not in seen:
                    queue.append((new_x, new_y))
        
        return False