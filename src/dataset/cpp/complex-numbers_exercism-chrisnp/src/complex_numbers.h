#pragma once

namespace complex_numbers {

class Complex {
private:
    double _real;
    double _imag;
public:
    Complex(double real, double imag);
    Complex(double real);
    [[nodiscard]] auto real() const -> double;
    [[nodiscard]] auto imag() const -> double;
    [[nodiscard]] auto abs() const -> double;
    [[nodiscard]] auto conj() const -> Complex;
    [[nodiscard]] auto exp() const -> Complex;
};

Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);
}  // namespace complex_numbers


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
