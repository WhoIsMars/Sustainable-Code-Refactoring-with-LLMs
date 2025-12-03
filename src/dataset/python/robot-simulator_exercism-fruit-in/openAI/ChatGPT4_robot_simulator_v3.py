EAST, NORTH, WEST, SOUTH = 1, 0, 3, 2

class Robot:
    def __init__(self, direction=NORTH, x=0, y=0):
        self.coordinates = (x, y)
        self.direction = direction

    def turn_right(self):
        self.direction = (self.direction + 1) % 4

    def turn_left(self):
        self.direction = (self.direction - 1) % 4

    def advance(self):
        x, y = self.coordinates
        moves = {NORTH: (0, 1), EAST: (1, 0), SOUTH: (0, -1), WEST: (-1, 0)}
        dx, dy = moves[self.direction]
        self.coordinates = (x + dx, y + dy)

    def move(self, instructions):
        actions = {
            'R': self.turn_right,
            'L': self.turn_left,
            'A': self.advance
        }
        for ins in instructions:
            actions[ins]()