EAST = 1
NORTH = 0
WEST = 3
SOUTH = 2


class Robot:
    __slots__ = ('coordinates', 'direction')

    def __init__(self, direction=NORTH, x=0, y=0):
        self.coordinates = (x, y)
        self.direction = direction

    def turn_right(self):
        self.direction = (self.direction + 1) & 3

    def turn_left(self):
        self.direction = (self.direction - 1) & 3

    def advance(self):
        x, y = self.coordinates
        if self.direction == NORTH:
            self.coordinates = (x, y + 1)
        elif self.direction == EAST:
            self.coordinates = (x + 1, y)
        elif self.direction == SOUTH:
            self.coordinates = (x, y - 1)
        else:  # self.direction == WEST:
            self.coordinates = (x - 1, y)

    def move(self, instructions):
        x_delta = (0, 1, 0, -1)
        y_delta = (1, 0, -1, 0)

        x, y = self.coordinates

        for ins in instructions:
            if ins == 'R':
                self.direction = (self.direction + 1) & 3
            elif ins == 'L':
                self.direction = (self.direction - 1) & 3
            elif ins == 'A':
                x += x_delta[self.direction]
                y += y_delta[self.direction]
                self.coordinates = (x, y)