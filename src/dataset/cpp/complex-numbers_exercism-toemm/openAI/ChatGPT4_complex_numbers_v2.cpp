#include "complex_numbers.h"

#include <cmath>
#include <iostream>

namespace complex_numbers {

    Complex::Complex(const double real, const double imag) noexcept : _real(real), _imag(imag) { }

    double Complex::real() const noexcept {
        return _real;
    }

    double Complex::imag() const noexcept {
        return _imag;
    }

    double Complex::abs() const noexcept {
        return std::hypot(_real, _imag); // More efficient and numerically stable
    }

    Complex Complex::conj() const noexcept {
        return {_real, -_imag};
    }

    Complex Complex::exp() const noexcept {
        const double A = std::exp(_real);
        return {A * std::cos(_imag), A * std::sin(_imag)};
    }

    Complex Complex::operator*(const Complex& rhs) const noexcept {
        return {_real * rhs._real - _imag * rhs._imag,
                _imag * rhs._real + _real * rhs._imag};
    }

    Complex Complex::operator*(const double& rhs) const noexcept {
        return {_real * rhs, _imag * rhs};
    }

    Complex Complex::operator+(const Complex& rhs) const noexcept {
        return {_real + rhs._real, _imag + rhs._imag};
    }

    Complex Complex::operator+(const double& rhs) const noexcept {
        return {_real + rhs, _imag};
    }

    Complex Complex::operator-(const Complex& rhs) const noexcept {
        return {_real - rhs._real, _imag - rhs._imag};
    }

    Complex Complex::operator-(const double& rhs) const noexcept {
        return {_real - rhs, _imag};
    }

    Complex Complex::operator/(const Complex& rhs) const noexcept {
        const double denom = rhs._real * rhs._real + rhs._imag * rhs._imag;
        return {(_real * rhs._real + _imag * rhs._imag) / denom,
                (_imag * rhs._real - _real * rhs._imag) / denom};
    }

    Complex Complex::operator/(const double& rhs) const noexcept {
        return {_real / rhs, _imag / rhs};
    }

    Complex operator-(const double& lhs, const Complex& rhs) noexcept {
        return {lhs - rhs.real(), -rhs.imag()};
    }

    Complex operator*(const double& lhs, const Complex& rhs) noexcept {
        return rhs * lhs;
    }

    Complex operator+(const double& lhs, const Complex& rhs) noexcept {
        return {lhs + rhs.real(), rhs.imag()};
    }

    Complex operator/(const double& lhs, const Complex& rhs) noexcept {
        const double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
        return {(lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom};
    }

}  // namespace complex_numbers