public class Triangle {
    private final double a, b, c;

    public Triangle(double a, double b, double c) throws TriangleException {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw new TriangleException();
        }
        if (a > b) {
            double temp = a;
            a = b;
            b = temp;
        }
        if (b > c) {
            double temp = b;
            b = c;
            c = temp;
        }
        if (a > b) {
            double temp = a;
            a = b;
            b = temp;
        }
        this.a = a;
        this.b = b;
        this.c = c;
        if (this.a + this.b <= this.c) {
            throw new TriangleException();
        }
    }

    public TriangleKind getKind() {
        if (a == c) {
            return TriangleKind.EQUILATERAL;
        } else if (a == b || b == c) {
            return TriangleKind.ISOSCELES;
        } else {
            return TriangleKind.SCALENE;
        }
    }
}