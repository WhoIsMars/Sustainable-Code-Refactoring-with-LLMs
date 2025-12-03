EAST = 1
NORTH = 0
WEST = 3
SOUTH = 2

DIRECTION_VECTORS = {
    NORTH: (0, 1),
    EAST: (1, 0),
    SOUTH: (0, -1),
    WEST: (-1, 0),
}

class Robot:
    def __init__(self, direction=NORTH, x=0, y=0):
        self.coordinates = (x, y)
        self.direction = direction

    def turn_right(self):
        self.direction = (self.direction + 1) % 4

    def turn_left(self):
        self.direction = (self.direction - 1) % 4

    def advance(self):
        dx, dy = DIRECTION_VECTORS[self.direction]
        x, y = self.coordinates
        self.coordinates = (x + dx, y + dy)

    def move(self, instructions):
        actions = {
            'R': self.turn_right,
            'L': self.turn_left,
            'A': self.advance,
        }
        for ins in instructions:
            actions[ins]()