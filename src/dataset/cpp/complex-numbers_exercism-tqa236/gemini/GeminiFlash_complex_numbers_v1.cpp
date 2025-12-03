#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {
Complex::Complex(double real_, double imag_) : real_(real_), imag_(imag_) {}
double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }
double Complex::abs() const { return std::hypot(real_, imag_); }
Complex Complex::operator+(Complex const &obj) const {
  return Complex(real_ + obj.real_, imag_ + obj.imag_);
}
Complex Complex::operator-(Complex const &obj) const {
  return Complex(real_ - obj.real_, imag_ - obj.imag_);
}
Complex Complex::operator*(Complex const &obj) const {
  const double real_part = real_ * obj.real_ - imag_ * obj.imag_;
  const double imag_part = imag_ * obj.real_ + real_ * obj.imag_;
  return Complex(real_part, imag_part);
}
Complex Complex::operator/(Complex const &obj) const {
  const double denominator = obj.real_ * obj.real_ + obj.imag_ * obj.imag_;
  const double real_part = (real_ * obj.real_ + imag_ * obj.imag_) / denominator;
  const double imag_part = (imag_ * obj.real_ - real_ * obj.imag_) / denominator;
  return Complex(real_part, imag_part);
}
Complex Complex::conj() const { return Complex(real_, -imag_); }
Complex Complex::exp() const {
  const double common_factor = std::exp(real_);
  return Complex(common_factor * std::cos(imag_), common_factor * std::sin(imag_));
}
}  // namespace complex_numbers