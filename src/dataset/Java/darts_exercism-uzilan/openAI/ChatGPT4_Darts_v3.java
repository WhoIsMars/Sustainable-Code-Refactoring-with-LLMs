class Darts {

    private final double radiusSquared;

    Darts(double x, double y) {
        radiusSquared = x * x + y * y;
    }

    int score() {
        if (radiusSquared > 100) {
            return 0;
        } else if (radiusSquared > 25) {
            return 1;
        } else if (radiusSquared > 1) {
            return 5;
        } else {
            return 10;
        }
    }
}