#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {
Complex::Complex(double real_, double imag_) : real_(real_), imag_(imag_) {}
double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }
double Complex::abs() const { return std::hypot(real_, imag_); }
Complex Complex::operator+(Complex const &obj) const {
  return {real_ + obj.real_, imag_ + obj.imag_};
}
Complex Complex::operator-(Complex const &obj) const {
  return {real_ - obj.real_, imag_ - obj.imag_};
}
Complex Complex::operator*(Complex const &obj) const {
  return {real_ * obj.real() - imag_ * obj.imag(),
          imag_ * obj.real() + real_ * obj.imag()};
}
Complex Complex::operator/(Complex const &obj) const {
  const double denominator = obj.real() * obj.real() + obj.imag() * obj.imag();
  const double real_part = (real_ * obj.real() + imag_ * obj.imag()) / denominator;
  const double imag_part = (imag_ * obj.real() - real_ * obj.imag()) / denominator;
  return {real_part, imag_part};
}
Complex Complex::conj() const { return {real_, -imag_}; }
Complex Complex::exp() const {
  const double exp_real = std::exp(real_);
  return {exp_real * std::cos(imag_), exp_real * std::sin(imag_)};
}
}  // namespace complex_numbers