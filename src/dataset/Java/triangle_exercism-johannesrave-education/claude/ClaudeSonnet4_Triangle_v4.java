class Triangle {

    private final double side1;
    private final double side2;
    private final double side3;
    private final int triangleType;
    
    private static final int SCALENE = 0;
    private static final int ISOSCELES = 1;
    private static final int EQUILATERAL = 2;

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
        this.triangleType = determineTriangleType();
    }
    
    private int determineTriangleType() {
        if (side1 == side2 && side2 == side3) {
            return EQUILATERAL;
        }
        if (side1 == side2 || side2 == side3 || side1 == side3) {
            return ISOSCELES;
        }
        return SCALENE;
    }

    boolean isEquilateral() {
        return triangleType == EQUILATERAL;
    }

    boolean isIsosceles() {
        return triangleType == ISOSCELES || triangleType == EQUILATERAL;
    }
        
    boolean isScalene() {
        return triangleType == SCALENE;
    }
}