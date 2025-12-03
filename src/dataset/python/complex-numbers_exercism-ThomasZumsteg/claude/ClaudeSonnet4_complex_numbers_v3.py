import math

class ComplexNumber:
    __slots__ = ('real', 'imaginary')
    
    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary

    def __add__(self, other):
        return ComplexNumber(
                self.real + other.real,
                self.imaginary + other.imaginary)

    def __mul__(self, other):
        return ComplexNumber(
                self.real * other.real - self.imaginary * other.imaginary,
                self.real * other.imaginary + self.imaginary * other.real)

    def __sub__(self, other):
        return ComplexNumber(
                self.real - other.real,
                self.imaginary - other.imaginary)

    def __truediv__(self, other):
        other_real_sq = other.real * other.real
        other_imag_sq = other.imaginary * other.imaginary
        common = other_real_sq + other_imag_sq
        real = (self.real * other.real + self.imaginary * other.imaginary) / common
        imaginary = (self.imaginary * other.real - self.real * other.imaginary) / common
        return ComplexNumber(real, imaginary)

    def __abs__(self):
        return math.sqrt(self.real * self.real + self.imaginary * self.imaginary)

    def conjugate(self):
        return ComplexNumber(self.real, -self.imaginary)

    def exp(self):
        exp_real = math.exp(self.real)
        cos_imag = math.cos(self.imaginary)
        sin_imag = math.sin(self.imaginary)
        return ComplexNumber(
                round(exp_real * cos_imag, 15),
                round(exp_real * sin_imag, 15))

    def __eq__(self, other):
        return self.real == other.real and self.imaginary == other.imaginary

    def __repr__(self):
        return f"{self.real} + {self.imaginary}i"