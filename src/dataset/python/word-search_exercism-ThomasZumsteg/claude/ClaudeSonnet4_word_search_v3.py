from collections import defaultdict
from itertools import product

class Point:
    __slots__ = ('x', 'y')
    
    def __init__(self, x, y):
        self.x = x 
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y


class WordSearch:
    dirs = tuple(prod for prod in product((0, 1, -1), repeat=2) if prod != (0,0))

    def __init__(self, puzzle):
        self._puzzle = puzzle
        self._puzzle_height = len(puzzle)
        self._puzzle_widths = [len(row) for row in puzzle]
        self._hashes = {}
        self._build_word_index()

    def _build_word_index(self):
        hashes = defaultdict(list)
        for r in range(self._puzzle_height):
            row = self._puzzle[r]
            for c in range(len(row)):
                start = Point(c, r)
                for word, end in self._words_starting_from(start):
                    hashes[word].append((start, end))
        self._hashes = dict(hashes)

    def _words_starting_from(self, start):
        char = self._puzzle[start.y][start.x]
        yield (char, start) 
        
        for dx, dy in self.dirs:
            word = char
            x, y = start.x, start.y
            
            while True:
                x += dx
                y += dy
                if not (0 <= y < self._puzzle_height and 0 <= x < self._puzzle_widths[y]):
                    break
                word += self._puzzle[y][x]
                yield (word, Point(x, y))

    def search(self, word):
        matches = self._hashes.get(word, [None])
        assert len(matches) == 1
        return matches[0]