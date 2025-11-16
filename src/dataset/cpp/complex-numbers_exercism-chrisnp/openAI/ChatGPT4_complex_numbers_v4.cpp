#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) noexcept : _real(real), _imag(imag) {}
Complex::Complex(double real) noexcept : _real(real), _imag(0.0) {}

double Complex::real() const noexcept { return _real; }
double Complex::imag() const noexcept { return _imag; }
double Complex::abs() const noexcept { 
  return std::hypot(_real, _imag);
}
Complex Complex::conj() const noexcept { return Complex(_real, -_imag); }
Complex Complex::exp() const noexcept {
  const double xp = std::exp(_real);
  return Complex(xp * std::cos(_imag), xp * std::sin(_imag));
}
Complex operator+(const Complex& x, const Complex& y) noexcept {
  return Complex(x._real + y._real, x._imag + y._imag);
}
Complex operator-(const Complex& x, const Complex& y) noexcept {
  return Complex(x._real - y._real, x._imag - y._imag);
}
Complex operator*(const Complex& x, const Complex& y) noexcept {
  return Complex(x._real * y._real - x._imag * y._imag, 
                 x._imag * y._real + x._real * y._imag);
}
Complex operator/(const Complex& x, const Complex& y) noexcept {
  const double d = y._real * y._real + y._imag * y._imag;
  return Complex((x._real * y._real + x._imag * y._imag) / d, 
                 (x._imag * y._real - x._real * y._imag) / d);
}
} // namespace complex_numbers