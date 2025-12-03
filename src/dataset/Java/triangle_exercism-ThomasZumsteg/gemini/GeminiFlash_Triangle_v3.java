import java.util.Arrays;

public class Triangle {
    private final double a, b, c;

    public Triangle(double a, double b, double c) throws TriangleException {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw new TriangleException();
        }

        if (a + b <= c || a + c <= b || b + c <= a) {
            throw new TriangleException();
        }

        double[] sides = {a, b, c};
        Arrays.sort(sides);
        this.a = sides[0];
        this.b = sides[1];
        this.c = sides[2];
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