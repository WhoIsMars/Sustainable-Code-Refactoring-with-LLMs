#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {
Complex::Complex(double real_, double imag_) : real_(real_), imag_(imag_) {}
double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }
double Complex::abs() const { return std::hypot(real_, imag_); }
Complex Complex::operator+(const Complex &obj) const {
  return {real_ + obj.real_, imag_ + obj.imag_};
}
Complex Complex::operator-(const Complex &obj) const {
  return {real_ - obj.real_, imag_ - obj.imag_};
}
Complex Complex::operator*(const Complex &obj) const {
  return {real_ * obj.real_ - imag_ * obj.imag_,
          imag_ * obj.real_ + real_ * obj.imag_};
}
Complex Complex::operator/(const Complex &obj) const {
  double denominator = obj.real_ * obj.real_ + obj.imag_ * obj.imag_;
  double inv_denominator = 1.0 / denominator;
  return {(real_ * obj.real_ + imag_ * obj.imag_) * inv_denominator,
          (imag_ * obj.real_ - real_ * obj.imag_) * inv_denominator};
}
Complex Complex::conj() const { return {real_, -imag_}; }
Complex Complex::exp() const {
  double common_factor = std::exp(real_);
  return {common_factor * std::cos(imag_), common_factor * std::sin(imag_)};
}
}  // namespace complex_numbers