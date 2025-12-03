import java.util.Arrays;

import static java.lang.Math.max;

class Triangle {

    private final int distinctSides;

    Triangle(double side1, double side2, double side3) throws TriangleException {
        double[] sides = {side1, side2, side3};
        Arrays.sort(sides);
        if (sides[2] >= sides[0] + sides[1]) {
            throw new TriangleException();
        }

        distinctSides = (int) (side1 == side2 ? (side2 == side3 ? 1 : 2) : (side2 == side3 || side1 == side3 ? 2 : 3));
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