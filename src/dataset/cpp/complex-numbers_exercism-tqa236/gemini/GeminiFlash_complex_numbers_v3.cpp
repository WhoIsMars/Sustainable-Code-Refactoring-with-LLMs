#include "complex_numbers.h"

#include <cmath>
#include <numbers>

namespace complex_numbers {

Complex::Complex(double real_, double imag_) noexcept : real_(real_), imag_(imag_) {}

double Complex::real() const noexcept { return real_; }

double Complex::imag() const noexcept { return imag_; }

double Complex::abs() const noexcept {
  return std::hypot(real_, imag_);
}

Complex Complex::operator+(Complex const &obj) const noexcept {
  return Complex(real_ + obj.real_, imag_ + obj.imag_);
}

Complex Complex::operator-(Complex const &obj) const noexcept {
  return Complex(real_ - obj.real_, imag_ - obj.imag_);
}

Complex Complex::operator*(Complex const &obj) const noexcept {
  return Complex(real_ * obj.real_ - imag_ * obj.imag_,
                 imag_ * obj.real_ + real_ * obj.imag_);
}

Complex Complex::operator/(Complex const &obj) const {
  const double denominator = obj.real_ * obj.real_ + obj.imag_ * obj.imag_;
  return Complex((real_ * obj.real_ + imag_ * obj.imag_) / denominator,
                 (imag_ * obj.real_ - real_ * obj.imag_) / denominator);
}

Complex Complex::conj() const noexcept { return Complex(real_, -imag_); }

Complex Complex::exp() const {
  const double exp_real = std::exp(real_);
  return Complex(exp_real * std::cos(imag_), exp_real * std::sin(imag_));
}

}  // namespace complex_numbers