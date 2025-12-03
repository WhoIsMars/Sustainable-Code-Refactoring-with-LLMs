public class Triangle {
    private double a, b, c;

    public Triangle(double a, double b, double c) throws TriangleException {
        // Sort manually without creating array or using Arrays.sort
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
        
        this.a = min;
        this.b = mid;
        this.c = max;
        
        if (min < 0 || min + mid <= max) {
            throw new TriangleException();
        }
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