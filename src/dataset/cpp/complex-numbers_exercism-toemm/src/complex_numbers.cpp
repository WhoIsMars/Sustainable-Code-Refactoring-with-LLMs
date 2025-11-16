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
            _real * rhs.real() - _imag * rhs.imag(),
            _imag * rhs.real() + _real * rhs.imag()};
    }

    Complex Complex::operator*(const double& rhs) const {
        return operator*(Complex{rhs, 0});
    }


    Complex Complex::operator+(const Complex& rhs) const {
        return Complex{_real + rhs.real(), _imag + rhs.imag()};
    }
    
    Complex Complex::operator+(const double& rhs) const {
        return operator+(Complex{rhs, 0});
    }

    Complex Complex::operator-(const double& rhs) const {
        return operator-(Complex{rhs, 0});
    }




    Complex Complex::operator-(const Complex& rhs) const {
        return Complex{_real - rhs.real(), _imag - rhs.imag()};
    }
    Complex Complex::operator/(const Complex& rhs) const {
        return Complex{(_real * rhs.real() + _imag * rhs.imag()) / (pow(rhs.real(), 2) + pow(rhs.imag(), 2)),
                       (_imag * rhs.real() - _real * rhs.imag()) / (pow(rhs.real(), 2) + pow(rhs.imag(), 2))};
    }

    Complex Complex::operator/(const double& rhs) const {
        return operator/(Complex{rhs, 0});
    }


    Complex operator-(const double& lhs, const Complex& rhs) {
        return Complex{lhs, 0}.operator-(rhs);
    }

    Complex operator*(const double& lhs, const Complex& rhs) {
        return rhs.operator*(lhs);
    }

    Complex operator+(const double& lhs, const Complex& rhs) {
        return rhs.operator+(lhs);
    }

    Complex operator/(const double& lhs, const Complex& rhs) {
        return Complex{lhs, 0}.operator/(rhs);
    }


}  // namespace complex_numbers
