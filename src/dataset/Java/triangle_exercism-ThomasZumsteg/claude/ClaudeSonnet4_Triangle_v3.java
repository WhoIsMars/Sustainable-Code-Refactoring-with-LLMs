import java.util.Arrays;

public class Triangle {
    private double a, b, c;

    public Triangle(double a, double b, double c) throws TriangleException {
        if (a < 0 || b < 0 || c < 0) {
            throw new TriangleException();
        }
        
        double min, mid, max;
        if (a <= b && a <= c) {
            min = a;
            if (b <= c) {
                mid = b;
                max = c;
            } else {
                mid = c;
                max = b;
            }
        } else if (b <= a && b <= c) {
            min = b;
            if (a <= c) {
                mid = a;
                max = c;
            } else {
                mid = c;
                max = a;
            }
        } else {
            min = c;
            if (a <= b) {
                mid = a;
                max = b;
            } else {
                mid = b;
                max = a;
            }
        }
        
        if (min + mid <= max) {
            throw new TriangleException();
        }
        
        this.a = min;
        this.b = mid;
        this.c = max;
    }

    public TriangleKind getKind() {
        if (a == b) {
            return (b == c) ? TriangleKind.EQUILATERAL : TriangleKind.ISOSCELES;
        } else if (b == c) {
            return TriangleKind.ISOSCELES;
        } else {
            return TriangleKind.SCALENE;
        }
    }
}