class Triangle {

    private final double side1;
    private final double side2;
    private final double side3;
    private final byte triangleType; // 0: scalene, 1: isosceles, 2: equilateral

    Triangle(double side1, double side2, double side3) throws TriangleException {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0){
            throw new TriangleException();
        }
        if (side1 + side2 <= side3 || side1 + side3 <= side2 || side3 + side2 <= side1){
            throw new TriangleException();
        }
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
        
        // Pre-compute triangle type once during construction
        if (side1 == side2 && side2 == side3) {
            this.triangleType = 2; // equilateral
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            this.triangleType = 1; // isosceles
        } else {
            this.triangleType = 0; // scalene
        }
    }

    boolean isEquilateral() {
        return triangleType == 2;
    }

    boolean isIsosceles() {
        return triangleType >= 1;
    }
        
    boolean isScalene() {
        return triangleType == 0;
    }
}