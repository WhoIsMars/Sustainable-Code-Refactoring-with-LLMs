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
        self.sides = sides

    def kind(self):
        """Specify triangle type"""
        a, b, c = self.sides
        if a == c:
            return "equilateral"
        elif a == b or b == c:
            return "isosceles"
        else:
            return "scalene"