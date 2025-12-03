import math

class ComplexNumber:
    __slots__ = ('real', 'imaginary')

    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary

    def __add__(self, other):
        return ComplexNumber(self.real + other.real, self.imaginary + other.imaginary)

    def __mul__(self, other):
        real, imaginary = self.real, self.imaginary
        return ComplexNumber(real * other.real - imaginary * other.imaginary,
                             real * other.imaginary + imaginary * other.real)

    def __sub__(self, other):
        return ComplexNumber(self.real - other.real, self.imaginary - other.imaginary)

    def __truediv__(self, other):
        common = other.real**2 + other.imaginary**2
        real, imaginary = self.real, self.imaginary
        return ComplexNumber((real * other.real + imaginary * other.imaginary) / common,
                             (imaginary * other.real - real * other.imaginary) / common)

    def __abs__(self):
        return math.hypot(self.real, self.imaginary)

    def conjugate(self):
        return ComplexNumber(self.real, -self.imaginary)

    def exp(self):
        exp_real = math.exp(self.real)
        return ComplexNumber(round(exp_real * math.cos(self.imaginary), 15),
                             round(exp_real * math.sin(self.imaginary), 15))

    def __eq__(self, other):
        return self.real == other.real and self.imaginary == other.imaginary

    def __repr__(self):
        return f"{self.real} + {self.imaginary}i"