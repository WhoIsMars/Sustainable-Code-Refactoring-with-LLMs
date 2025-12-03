class Darts {

    private final double radiusSquared;

    Darts(double x, double y) {
        radiusSquared = x * x + y * y;
    }

    int score() {
        if (radiusSquared > 100) {
            return 0;
        }
        if (radiusSquared > 25) {
            return 1;
        }
        if (radiusSquared > 1) {
            return 5;
        }
        return 10;
    }
}