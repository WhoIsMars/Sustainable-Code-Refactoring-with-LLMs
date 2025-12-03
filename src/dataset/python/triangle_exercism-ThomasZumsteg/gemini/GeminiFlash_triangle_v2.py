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
        self.a, self.b, self.c = sides[0], sides[1], sides[2]

        if self.a + self.b <= self.c:
            raise TriangleError("Not a Triangle")

    def kind(self):
        """Specify triangle type"""
        if self.a == self.b:
            if self.b == self.c:
                return "equilateral"
            else:
                return "isosceles"
        elif self.b == self.c:
            return "isosceles"
        else:
            return "scalene"