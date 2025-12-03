public class Triangle {
    private double a, b, c;

    public Triangle(double a, double b, double c) throws TriangleException {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw new TriangleException();
        }

        if (a + b <= c || a + c <= b || b + c <= a) {
            throw new TriangleException();
        }

        this.a = a;
        this.b = b;
        this.c = c;
    }

    public TriangleKind getKind() {
        if (a == b) {
            if (b == c) {
                return TriangleKind.EQUILATERAL;
            } else {
                return TriangleKind.ISOSCELES;
            }
        } else if (b == c || a == c) {
            return TriangleKind.ISOSCELES;
        } else {
            return TriangleKind.SCALENE;
        }
    }
}