#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

    constexpr double M_E = 2.71828182845904523536;
    constexpr double M_PI = 3.14159265358979323846;


class Complex final {
    
    public:

    explicit Complex(const double real, const double imag=0.0);
    double real() const noexcept;
    double imag() const noexcept;
    double abs() const noexcept;
    Complex conj() const noexcept;
    Complex exp() const noexcept;

    Complex operator*(const Complex& rhs) const;
    Complex operator*(const double& rhs) const;
    Complex operator+(const Complex& rhs) const;
    Complex operator+(const double& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator-(const double& rhs) const;
    Complex operator/(const Complex& rhs) const;
    Complex operator/(const double& rhs) const;

    private:

    double _real;
    double _imag;

};

Complex operator-(const double& lhs, const Complex& rhs);
Complex operator*(const double& lhs, const Complex& rhs);
Complex operator+(const double& lhs, const Complex& rhs);
Complex operator/(const double& lhs, const Complex& rhs);



}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
