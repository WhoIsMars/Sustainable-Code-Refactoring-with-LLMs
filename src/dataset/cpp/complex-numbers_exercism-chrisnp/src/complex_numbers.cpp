#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : _real(real), _imag(imag) {}
Complex::Complex(double real) : _real(real) {}

double Complex::real() const { return _real; }
double Complex::imag() const { return _imag; }
double Complex::abs() const { 
  return std::sqrt(_real * _real + _imag * _imag);
}
Complex Complex::conj() const { return Complex(_real, -_imag); }
Complex Complex::exp() const {
  auto xp = std::exp(_real);
  auto r = xp * std::cos(_imag);
  auto i = xp * std::sin(_imag);
  return Complex(r, i);
}
Complex operator+(const Complex& x, const Complex& y) {
  auto r = x.real() + y.real();
  auto i = x.imag() + y.imag();
  return Complex(r, i);
}
Complex operator-(const Complex& x, const Complex& y) {
  auto r = x.real() - y.real();
  auto i = x.imag() - y.imag();
  return Complex(r, i);
}
Complex operator*(const Complex& x, const Complex& y) {
  auto r = x.real() * y.real() - x.imag() * y.imag();
  auto i = x.imag() * y.real() + x.real() * y.imag();
  return Complex(r, i);
}
Complex operator/(const Complex& x, const Complex& y) {
  auto d = y.real() * y.real() + y.imag() * y.imag();
  auto r = (x.real() * y.real() + x.imag() * y.imag()) / d;
  auto i = (x.imag() * y.real() - x.real() * y.imag()) / d;
  return Complex(r, i);
}
} // namespace complex_numbers