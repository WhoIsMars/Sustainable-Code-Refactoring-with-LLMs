import cmath


class ComplexNumber:
    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary

    def __eq__(self, other):
        return self.real == other.real and self.imaginary == other.imaginary

    def __add__(self, other):
        return ComplexNumber(self.real + other.real, self.imaginary + other.imaginary)

    def __mul__(self, other):
        real = self.real * other.real - self.imaginary * other.imaginary
        imaginary = self.imaginary * other.real + self.real * other.imaginary
        return ComplexNumber(real, imaginary)

    def __sub__(self, other):
        return ComplexNumber(self.real - other.real, self.imaginary - other.imaginary)

    def __truediv__(self, other):
        abs_other_sq = other.real**2 + other.imaginary**2
        real = (self.real * other.real + self.imaginary * other.imaginary) / abs_other_sq
        imaginary = (self.imaginary * other.real - self.real * other.imaginary) / abs_other_sq
        return ComplexNumber(real, imaginary)

    def __abs__(self):
        return (self.real**2 + self.imaginary**2)**0.5

    def conjugate(self):
        return ComplexNumber(self.real, -self.imaginary)

    def exp(self):
        exponential = cmath.exp(complex(self.real, self.imaginary))
        return ComplexNumber(exponential.real, exponential.imag)