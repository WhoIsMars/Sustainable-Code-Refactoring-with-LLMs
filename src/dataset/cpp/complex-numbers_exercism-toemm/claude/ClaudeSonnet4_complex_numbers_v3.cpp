#include "complex_numbers.h"

#include <cmath>
#include <iostream>

namespace complex_numbers {

    Complex::Complex(const double real, const double imag): _real(real), _imag(imag) { }

    double Complex::real() const noexcept {
        return _real;
    }

    double Complex::imag() const noexcept {
        return _imag;
    }

    double Complex::abs() const noexcept {
        return std::sqrt(_real*_real + _imag*_imag);
    }

    Complex Complex::conj() const noexcept {
        return Complex{_real, -_imag};
    }

    Complex Complex::exp() const noexcept {
        const double A = std::exp(_real);
        return Complex(A * std::cos(_imag), A * std::sin(_imag));
    }

    Complex Complex::operator*(const Complex& rhs) const {
        return Complex{
            _real * rhs._real - _imag * rhs._imag,
            _imag * rhs._real + _real * rhs._imag};
    }

    Complex Complex::operator*(const double& rhs) const {
        return Complex{_real * rhs, _imag * rhs};
    }

    Complex Complex::operator+(const Complex& rhs) const {
        return Complex{_real + rhs._real, _imag + rhs._imag};
    }
    
    Complex Complex::operator+(const double& rhs) const {
        return Complex{_real + rhs, _imag};
    }

    Complex Complex::operator-(const double& rhs) const {
        return Complex{_real - rhs, _imag};
    }

    Complex Complex::operator-(const Complex& rhs) const {
        return Complex{_real - rhs._real, _imag - rhs._imag};
    }

    Complex Complex::operator/(const Complex& rhs) const {
        const double denominator = rhs._real * rhs._real + rhs._imag * rhs._imag;
        return Complex{(_real * rhs._real + _imag * rhs._imag) / denominator,
                       (_imag * rhs._real - _real * rhs._imag) / denominator};
    }

    Complex Complex::operator/(const double& rhs) const {
        return Complex{_real / rhs, _imag / rhs};
    }

    Complex operator-(const double& lhs, const Complex& rhs) {
        return Complex{lhs - rhs._real, -rhs._imag};
    }

    Complex operator*(const double& lhs, const Complex& rhs) {
        return Complex{lhs * rhs._real, lhs * rhs._imag};
    }

    Complex operator+(const double& lhs, const Complex& rhs) {
        return Complex{lhs + rhs._real, rhs._imag};
    }

    Complex operator/(const double& lhs, const Complex& rhs) {
        const double denominator = rhs._real * rhs._real + rhs._imag * rhs._imag;
        return Complex{lhs * rhs._real / denominator, -lhs * rhs._imag / denominator};
    }

}  // namespace complex_numbers