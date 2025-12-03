"""Validate and specify triangle types"""

class TriangleError(Exception):
    """Error if it cannot be a triangle"""
    pass

class Triangle:
    """Validate and specify triangle types"""
    __slots__ = ('a', 'b', 'c')
    
    def __init__(self, a, b, c):
        """Create and validate triangle"""
        sides = (a, b, c)
        min_side = min(sides)
        max_side = max(sides)
        mid_side = a + b + c - min_side - max_side
        
        if min_side + mid_side <= max_side:
            raise TriangleError("Not a Triangle")
        
        self.a, self.b, self.c = min_side, mid_side, max_side

    def kind(self):
        """Specify triangle type"""
        if self.a == self.c:
            return "equilateral"
        elif self.a == self.b or self.b == self.c:
            return "isosceles"
        else:
            return "scalene"