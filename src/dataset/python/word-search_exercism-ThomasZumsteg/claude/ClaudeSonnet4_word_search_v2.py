from collections import defaultdict

class Point(object):
    __slots__ = ('x', 'y')
    
    def __init__(self, x, y):
        self.x = x 
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y


class WordSearch(object):
    dirs = ((-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1))

    def __init__(self, puzzle):
        hashes = defaultdict(list)
        puzzle_height = len(puzzle)
        puzzle_widths = [len(row) for row in puzzle]
        
        for r in range(puzzle_height):
            puzzle_width = puzzle_widths[r]
            for c in range(puzzle_width):
                start = Point(c, r)
                for word, end in self._words_starting_from(puzzle, start, puzzle_height, puzzle_widths):
                    hashes[word].append((start, end))
        self._hashes = dict(hashes)

    def _words_starting_from(self, puzzle, start, puzzle_height, puzzle_widths):
        char = puzzle[start.y][start.x]
        yield (char, start) 
        queue = [(char, start.x, start.y, dx, dy) for dx, dy in self.dirs]
        
        while queue:
            word, x, y, dx, dy = queue.pop()
            new_x, new_y = x + dx, y + dy
            if 0 <= new_y < puzzle_height and 0 <= new_x < puzzle_widths[new_y]:
                word += puzzle[new_y][new_x]
                yield(word, Point(new_x, new_y))
                queue.append((word, new_x, new_y, dx, dy))

    def search(self, word):
        matches = self._hashes.get(word, [None])
        assert len(matches) == 1
        return matches[0]