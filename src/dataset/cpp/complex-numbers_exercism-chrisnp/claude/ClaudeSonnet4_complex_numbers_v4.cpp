#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : _real(real), _imag(imag) {}
Complex::Complex(double real) : _real(real), _imag(0.0) {}

double Complex::real() const { return _real; }
double Complex::imag() const { return _imag; }
double Complex::abs() const { 
  return std::sqrt(_real * _real + _imag * _imag);
}
Complex Complex::conj() const { return Complex(_real, -_imag); }
Complex Complex::exp() const {
  const double exp_real = std::exp(_real);
  return Complex(exp_real * std::cos(_imag), exp_real * std::sin(_imag));
}
Complex operator+(const Complex& x, const Complex& y) {
  return Complex(x._real + y._real, x._imag + y._imag);
}
Complex operator-(const Complex& x, const Complex& y) {
  return Complex(x._real - y._real, x._imag - y._imag);
}
Complex operator*(const Complex& x, const Complex& y) {
  return Complex(x._real * y._real - x._imag * y._imag, 
                 x._imag * y._real + x._real * y._imag);
}
Complex operator/(const Complex& x, const Complex& y) {
  const double denominator = y._real * y._real + y._imag * y._imag;
  return Complex((x._real * y._real + x._imag * y._imag) / denominator,
                 (x._imag * y._real - x._real * y._imag) / denominator);
}
} // namespace complex_numbers