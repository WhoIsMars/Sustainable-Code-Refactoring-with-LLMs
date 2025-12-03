"""Validate and specify triangle types"""

class TriangleError(Exception):
    """Error if it cannot be a triangle"""
    pass

class Triangle:
    """Validate and specify triangle types"""
    __slots__ = ('a', 'b', 'c')
    
    def __init__(self, a, b, c):
        """Create and validate triangle"""
        sides = sorted((a, b, c))
        self.a, self.b, self.c = sides
        if sides[0] + sides[1] <= sides[2]:
            raise TriangleError("Not a Triangle")

    def kind(self):
        """Specify triangle type"""
        if self.a == self.c:
            return "equilateral"
        elif self.a == self.b or self.b == self.c:
            return "isosceles"
        else:
            return "scalene"