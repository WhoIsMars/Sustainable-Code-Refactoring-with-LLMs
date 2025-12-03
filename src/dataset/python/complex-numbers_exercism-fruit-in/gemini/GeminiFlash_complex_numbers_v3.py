import cmath
import math


class ComplexNumber:
    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary
        self._complex = complex(real, imaginary)

    def __eq__(self, other):
        return self._complex == other._complex

    def __add__(self, other):
        result = self._complex + other._complex
        return ComplexNumber(result.real, result.imag)

    def __mul__(self, other):
        result = self._complex * other._complex
        return ComplexNumber(result.real, result.imag)

    def __sub__(self, other):
        result = self._complex - other._complex
        return ComplexNumber(result.real, result.imag)

    def __truediv__(self, other):
        result = self._complex / other._complex
        return ComplexNumber(result.real, result.imag)

    def __abs__(self):
        return abs(self._complex)

    def conjugate(self):
        return ComplexNumber(self.real, -self.imaginary)

    def exp(self):
        result = cmath.exp(self._complex)
        return ComplexNumber(result.real, result.imag)