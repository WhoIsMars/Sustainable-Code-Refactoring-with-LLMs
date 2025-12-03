from collections import defaultdict
from itertools import product

class Point(object):
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
        self.puzzle = puzzle
        self.rows = len(puzzle)
        self.cols = len(puzzle[0]) if self.rows > 0 else 0
        self._hashes = self._build_hashes()

    def _build_hashes(self):
        hashes = defaultdict(list)
        for r in range(self.rows):
            for c in range(self.cols):
                start = Point(c, r)
                for word, end in self._words_starting_from(start):
                    hashes[word].append((start, end))
        return dict(hashes)

    def _words_starting_from(self, start):
        x, y = start.x, start.y
        char = self.puzzle[y][x]
        yield (char, start)
        queue = [(char, x, y, dx, dy) for dx, dy in self.dirs]
        while queue:
            word, x, y, dx, dy = queue.pop()
            nx, ny = x + dx, y + dy
            if 0 <= ny < self.rows and 0 <= nx < self.cols:
                next_char = self.puzzle[ny][nx]
                next_word = word + next_char
                yield (next_word, Point(nx, ny))
                queue.append((next_word, nx, ny, dx, dy))

    def search(self, word):
        return self._hashes.get(word, [None])[0]