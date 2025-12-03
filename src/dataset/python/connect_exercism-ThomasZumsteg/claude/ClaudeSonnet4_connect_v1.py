class ConnectGame:
    def __init__(self, board):
        self._board = [line.split() for line in board.splitlines()]
        self._rows = len(self._board)
        self._cols = len(self._board[0])
        
        self._players = {
            'X': (
                tuple((0, r) for r in range(self._rows)),
                tuple((self._cols-1, r) for r in range(self._rows))
            ),
            'O': (
                tuple((c, 0) for c in range(self._cols)),
                tuple((c, self._rows-1) for c in range(self._cols))
            )
        }
        
        # Pre-compute neighbor offsets
        self._neighbors = ((0,-1),(1,-1),(-1,0),(1,0),(-1,1),(0,1))

    def get_winner(self):
        for player in self._players:
            if self._find_path(player):
                return player 
        return ''

    def _find_path(self, player):
        start, end = self._players[player]
        end_set = set(end)  # Convert to set for O(1) lookup
        
        # Use deque for better performance than list.pop()
        from collections import deque
        queue = deque(start)
        seen = set()
        
        while queue:
            x, y = queue.popleft()
            if (x, y) in seen:
                continue
            seen.add((x, y))
            
            # Bounds check first (cheaper)
            if not (0 <= y < self._rows and 0 <= x < self._cols):
                continue
            if self._board[y][x] != player:
                continue
                
            if (x, y) in end_set:
                return True
                
            # Add valid neighbors
            for dx, dy in self._neighbors:
                nx, ny = x + dx, y + dy
                if (nx, ny) not in seen:
                    queue.append((nx, ny))
        
        return False