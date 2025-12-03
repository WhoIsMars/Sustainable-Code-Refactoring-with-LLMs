from collections import defaultdict
from itertools import product

class Point(object):
    __slots__ = ('x', 'y')

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))


class WordSearch(object):
    dirs = tuple(prod for prod in product((0, 1, -1), repeat=2) if prod != (0,0))

    def __init__(self, puzzle):
        self._puzzle = puzzle
        self._height = len(puzzle)
        self._width = len(puzzle[0]) if self._height > 0 else 0
        self._hashes = self._build_hashes()

    def _build_hashes(self):
        hashes = defaultdict(list)
        for r in range(self._height):
            for c in range(self._width):
                for word, end in self._words_starting_from(c, r):
                    hashes[word].append((Point(c, r), end))
        return dict(hashes)

    def _words_starting_from(self, start_x, start_y):
        char = self._puzzle[start_y][start_x]
        yield (char, Point(start_x, start_y))
        queue = [(char, start_x, start_y, dx, dy) for dx, dy in self.dirs]
        while queue:
            word, x, y, dx, dy = queue.pop()
            nx, ny = x + dx, y + dy
            if 0 <= ny < self._height and 0 <= nx < self._width:
                next_char = self._puzzle[ny][nx]
                next_word = word + next_char
                yield (next_word, Point(nx, ny))
                queue.append((next_word, nx, ny, dx, dy))

    def search(self, word):
        matches = self._hashes.get(word)
        if matches:
            assert len(matches) == 1
            return matches[0]
        return None