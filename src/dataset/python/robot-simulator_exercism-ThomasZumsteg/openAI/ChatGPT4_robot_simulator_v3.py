NORTH, EAST, SOUTH, WEST = 0, 1, 2, 3

class Robot:
    _valid_commands = {
        'R': 'turn_right',
        'L': 'turn_left',
        'A': 'advance',
    }

    _direction_moves = {
        NORTH: (0, 1),
        EAST: (1, 0),
        SOUTH: (0, -1),
        WEST: (-1, 0),
    }

    def __init__(self, bearing=NORTH, x=0, y=0):
        self.bearing = bearing
        self.coordinates = (x, y)

    def turn_right(self):
        self.bearing = (self.bearing + 1) % 4

    def turn_left(self):
        self.bearing = (self.bearing - 1) % 4

    def advance(self):
        dx, dy = self._direction_moves[self.bearing]
        x, y = self.coordinates
        self.coordinates = (x + dx, y + dy)

    def simulate(self, commands):
        for c in commands:
            getattr(self, self._valid_commands[c])()