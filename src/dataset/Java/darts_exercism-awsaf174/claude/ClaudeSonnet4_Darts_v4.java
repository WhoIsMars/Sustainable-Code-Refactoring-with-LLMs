class Darts {
    private final double distanceSquared;
    
    Darts(double x, double y) {
        distanceSquared = x * x + y * y;
    }

    int score() {
        if (distanceSquared <= 1.0) {
            return 10;
        } else if (distanceSquared <= 25.0) {
            return 5;
        } else if (distanceSquared <= 100.0) {
            return 1;
        } else {
            return 0;
        }
    }
}