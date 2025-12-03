class Triangle {

    private final int distinctSides;

    Triangle(double side1, double side2, double side3) throws TriangleException {
        if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
            throw new TriangleException();
        }

        int distinctCount = 1;
        if (side1 != side2) {
            distinctCount++;
            if (side1 != side3 && side2 != side3) {
                distinctCount++;
            }
        } else if (side1 != side3) {
            distinctCount++;
        }

        distinctSides = distinctCount;
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