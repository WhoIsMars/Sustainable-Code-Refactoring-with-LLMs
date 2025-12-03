"""Validate and specify triangle types"""

class TriangleError(Exception):
    """Error if it cannot be a triangle"""
    def __init__(self, message):
        super().__init__(message)

class Triangle(object):
    """Validate and specify triangle types"""
    def __init__(self, a, b, c):
        """Create and validate triangle"""
        sides = sorted((a, b, c))
        if sides[0] + sides[1] <= sides[2]:
            raise TriangleError("Not a Triangle")
        self.a = sides[0]
        self.b = sides[1]
        self.c = sides[2]

    def kind(self):
        """Specify triangle type"""
        if self.a == self.c:
            return "equilateral"
        elif self.a == self.b or self.b == self.c:
            return "isosceles"
        else:
            return "scalene"