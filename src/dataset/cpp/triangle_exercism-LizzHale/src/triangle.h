#if !defined(TRIANGLE_H)
#define TRIANGLE_H

namespace triangle {
    enum class flavor {
        equilateral,
        scalene,
        isosceles
    };

    flavor kind(double s1, double s2, double s3);
    bool is_legal_triangle(double s1, double s2, double s3);
}  // namespace triangle

#endif // TRIANGLE_H