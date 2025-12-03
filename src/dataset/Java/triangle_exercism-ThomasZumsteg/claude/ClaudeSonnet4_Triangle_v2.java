public class Triangle {
    private double a, b, c;

    public Triangle(double a, double b, double c) throws TriangleException {
        // Sort manually to avoid array allocation and Arrays.sort overhead
        if (a > b) {
            if (b > c) {
                // a > b > c
                this.c = a; this.b = b; this.a = c;
            } else if (a > c) {
                // a > c >= b
                this.c = a; this.b = c; this.a = b;
            } else {
                // c >= a > b
                this.c = c; this.b = a; this.a = b;
            }
        } else {
            if (a > c) {
                // b >= a > c
                this.c = b; this.b = a; this.a = c;
            } else if (b > c) {
                // b > c >= a
                this.c = b; this.b = c; this.a = a;
            } else {
                // c >= b >= a
                this.c = c; this.b = b; this.a = a;
            }
        }
        
        if (this.a < 0 || this.a + this.b <= this.c) {
            throw new TriangleException();
        }
    }

    public TriangleKind getKind() {
        if (a == b) {
            return b == c ? TriangleKind.EQUILATERAL : TriangleKind.ISOSCELES;
        } else {
            return b == c ? TriangleKind.ISOSCELES : TriangleKind.SCALENE;
        }
    }
}