class TriangleError(Exception):
    def __init__(self, message):
        super().__init__(message)

class Triangle:
    def __init__(self, a, b, c):
        self.a, self.b, self.c = sorted((a, b, c))
        if self.a + self.b <= self.c:
            raise TriangleError("Not a Triangle")

    def kind(self):
        if self.a == self.c:
            return "equilateral"
        if self.a == self.b or self.b == self.c:
            return "isosceles"
        return "scalene"