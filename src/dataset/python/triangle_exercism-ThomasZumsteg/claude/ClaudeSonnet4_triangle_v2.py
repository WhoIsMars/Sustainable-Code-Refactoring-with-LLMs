"""Validate and specify triangle types"""

class TriangleError(Exception):
    """Error if it cannot be a triangle"""
    pass

class Triangle:
    """Validate and specify triangle types"""
    __slots__ = ('a', 'b', 'c')
    
    def __init__(self, a, b, c):
        """Create and validate triangle"""
        if a > b:
            if a > c:
                if b > c:
                    self.a, self.b, self.c = c, b, a
                else:
                    self.a, self.b, self.c = b, c, a
            else:
                self.a, self.b, self.c = b, a, c
        else:
            if b > c:
                if a > c:
                    self.a, self.b, self.c = c, a, b
                else:
                    self.a, self.b, self.c = a, c, b
            else:
                self.a, self.b, self.c = a, b, c
        
        if self.a + self.b <= self.c:
            raise TriangleError("Not a Triangle")

    def kind(self):
        """Specify triangle type"""
        if self.a == self.c:
            return "equilateral"
        elif self.a == self.b or self.b == self.c:
            return "isosceles"
        else:
            return "scalene"