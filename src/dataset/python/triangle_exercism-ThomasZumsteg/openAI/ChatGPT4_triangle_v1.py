"""Validate and specify triangle types"""

class TriangleError(Exception):
    """Error if it cannot be a triangle"""
    pass

class Triangle:
    """Validate and specify triangle types"""
    def __init__(self, a, b, c):
        """Create and validate triangle"""
        self.a, self.b, self.c = sorted((a, b, c))
        if self.a + self.b <= self.c:
            raise TriangleError("Not a Triangle")

    def kind(self):
        """Specify triangle type"""
        if self.a == self.c:
            return "equilateral"
        return "isosceles" if self.a == self.b or self.b == self.c else "scalene"