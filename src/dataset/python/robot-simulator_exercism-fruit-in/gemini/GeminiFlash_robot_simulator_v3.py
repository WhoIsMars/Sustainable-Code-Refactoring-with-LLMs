EAST = 1
NORTH = 0
WEST = 3
SOUTH = 2


class Robot:
    _DIRECTIONS = {
        NORTH: (0, 1),
        EAST: (1, 0),
        SOUTH: (0, -1),
        WEST: (-1, 0),
    }

    def __init__(self, direction=NORTH, x=0, y=0):
        self.coordinates = (x, y)
        self.direction = direction

    def turn_right(self):
        self.direction = (self.direction + 1) % 4

    def turn_left(self):
        self.direction = (self.direction - 1) % 4

    def advance(self):
        x, y = self.coordinates
        dx, dy = self._DIRECTIONS[self.direction]
        self.coordinates = (x + dx, y + dy)

    def move(self, instructions):
        for ins in instructions:
            if ins == 'R':
                self.turn_right()
            elif ins == 'L':
                self.turn_left()
            elif ins == 'A':
                self.advance()