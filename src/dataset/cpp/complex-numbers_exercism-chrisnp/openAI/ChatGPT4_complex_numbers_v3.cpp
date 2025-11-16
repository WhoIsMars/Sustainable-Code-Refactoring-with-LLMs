#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : _real(real), _imag(imag) {}
Complex::Complex(double real) : _real(real), _imag(0.0) {}

double Complex::real() const { return _real; }
double Complex::imag() const { return _imag; }
double Complex::abs() const { 
  return std::hypot(_real, _imag);
}
Complex Complex::conj() const { return {_real, -_imag}; }
Complex Complex::exp() const {
  double xp = std::exp(_real);
  return {xp * std::cos(_imag), xp * std::sin(_imag)};
}
Complex operator+(const Complex& x, const Complex& y) {
  return {x._real + y._real, x._imag + y._imag};
}
Complex operator-(const Complex& x, const Complex& y) {
  return {x._real - y._real, x._imag - y._imag};
}
Complex operator*(const Complex& x, const Complex& y) {
  return {x._real * y._real - x._imag * y._imag, x._imag * y._real + x._real * y._imag};
}
Complex operator/(const Complex& x, const Complex& y) {
  double d = y._real * y._real + y._imag * y._imag;
  return {(x._real * y._real + x._imag * y._imag) / d, (x._imag * y._real - x._real * y._imag) / d};
}
} // namespace complex_numbers