# NORTH, EAST, SOUTH, WEST are directions a robot can face
NORTH, EAST, SOUTH, WEST = 0, 1, 2, 3

class Robot:
    """Robot is a simulation of a robot"""

    # Commands that the robot can be given
    _valid_commands = {
        'R': 'turn_right',
        'L': 'turn_left',
        'A': 'advance',
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
        """advance moves the robot one space forward in the direction it's facing"""
        x, y = self.coordinates
        moves = {
            NORTH: (x, y + 1),
            SOUTH: (x, y - 1),
            EAST: (x + 1, y),
            WEST: (x - 1, y),
        }
        self.coordinates = moves[self.bearing]

    def simulate(self, commands):
        """simulate gives the robot a set of commands"""
        for c in commands:
            getattr(self, Robot._valid_commands[c])()