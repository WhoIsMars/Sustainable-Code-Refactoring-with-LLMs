import static java.lang.Math.max;

class Triangle {

    private final int distinctSides;

    Triangle(double side1, double side2, double side3) throws TriangleException {
        final double max = max(side1, max(side2, side3));
        if (max * 2 >= side1 + side2 + side3) {
            throw new TriangleException();
        }

        if (side1 == side2 && side2 == side3) {
            distinctSides = 1;
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            distinctSides = 2;
        } else {
            distinctSides = 3;
        }
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