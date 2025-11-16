#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {
Complex::Complex(double real_, double imag_) : real_(real_), imag_(imag_) {}
double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }
double Complex::abs() const { return std::sqrt(real_ * real_ + imag_ * imag_); }
Complex Complex::operator+(Complex const &obj) const {
  return Complex(real_ + obj.real_, imag_ + obj.imag_);
}
Complex Complex::operator-(Complex const &obj) const {
  return Complex(real_ - obj.real_, imag_ - obj.imag_);
}
Complex Complex::operator*(Complex const &obj) const {
  return Complex(real_ * obj.real_ - imag_ * obj.imag_,
                 imag_ * obj.real_ + real_ * obj.imag_);
}
Complex Complex::operator/(Complex const &obj) const {
  const double denominator = obj.real_ * obj.real_ + obj.imag_ * obj.imag_;
  const double inv_denom = 1.0 / denominator;
  return Complex((real_ * obj.real_ + imag_ * obj.imag_) * inv_denom,
                 (imag_ * obj.real_ - real_ * obj.imag_) * inv_denom);
}
Complex Complex::conj() const { return Complex(real_, -imag_); }
Complex Complex::exp() const {
  const double common_factor = std::exp(real_);
  double sin_val, cos_val;
  sin_val = std::sin(imag_);
  cos_val = std::cos(imag_);
  return Complex(common_factor * cos_val, common_factor * sin_val);
}
}  // namespace complex_numbers