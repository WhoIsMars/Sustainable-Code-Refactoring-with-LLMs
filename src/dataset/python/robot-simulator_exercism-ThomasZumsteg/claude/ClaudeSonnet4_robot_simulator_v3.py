# NORTH, EAST, SOUTH, WEST are directions a robot can face
NORTH, EAST, SOUTH, WEST = 0, 1, 2, 3

class Robot:
    """Robot is a simulation of a robot"""

    # Commands that the robot can be given
    _valid_commdands = {
        'R': 'turn_right',
        'L': 'turn_left',
        'A': 'advance',
    }
    
    # Pre-computed direction vectors for movement
    _direction_vectors = {
        NORTH: (0, 1),
        EAST: (1, 0),
        SOUTH: (0, -1),
        WEST: (-1, 0)
    }

    def __init__(self, bearing=NORTH, x=0, y=0):
        """__init__ creates the robot, defaults to facing north at the origin"""
        self.bearing = bearing
        self.coordinates = (x, y)

    def turn_right(self):
        """turn_right turns the robot to the right"""
        self.bearing = (self.bearing + 1) % 4

    def turn_left(self):
        """turn_left turns the robot to the left"""
        self.bearing = (self.bearing - 1) % 4

    def advance(self):
        """advance moves the robot one spce forward in the direction it's facing"""
        x, y = self.coordinates
        dx, dy = Robot._direction_vectors[self.bearing]
        self.coordinates = (x + dx, y + dy)

    def simulate(self, commands):
        """simulate give the robot a set of commands"""
        for c in commands:
            if c == 'R':
                self.turn_right()
            elif c == 'L':
                self.turn_left()
            elif c == 'A':
                self.advance()