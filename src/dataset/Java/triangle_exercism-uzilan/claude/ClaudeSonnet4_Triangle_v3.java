import static java.lang.Math.max;

class Triangle {

    private final byte distinctSides;

    Triangle(double side1, double side2, double side3) throws TriangleException {
        final double max = max(side1, max(side2, side3));
        if (max * 2 >= side1 + side2 + side3) {
            throw new TriangleException();
        }

        byte count = 1;
        if (side1 != side2) count++;
        if (side1 != side3 && side2 != side3) count++;
        
        distinctSides = count;
    }

    boolean isEquilateral() {
        return distinctSides == 1;
    }

    boolean isIsosceles() {
        return distinctSides <= 2;
    }

    boolean isScalene() {
        return distinctSides == 3;
    }
}