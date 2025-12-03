class Triangle {

    private final double side1;
    private final double side2;
    private final double side3;
    private final boolean isEquilateral;
    private final boolean isIsosceles;
    private final boolean isScalene;

    Triangle(double side1, double side2, double side3) throws TriangleException {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0 || 
            side1 + side2 <= side3 || side1 + side3 <= side2 || side3 + side2 <= side1) {
            throw new TriangleException();
        }
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
        this.isEquilateral = (side1 == side2 && side2 == side3);
        this.isIsosceles = !isEquilateral && (side1 == side2 || side2 == side3 || side1 == side3);
        this.isScalene = !isEquilateral && !isIsosceles;
    }

    boolean isEquilateral() {
        return isEquilateral;
    }

    boolean isIsosceles() {
        return isIsosceles;
    }

    boolean isScalene() {
        return isScalene;
    }
}