class Darts {

    private final int score;

    Darts(double x, double y) {
        double radiusSquared = x * x + y * y;
        if (radiusSquared > 100) {
            score = 0;
        } else if (radiusSquared > 25) {
            score = 1;
        } else if (radiusSquared > 1) {
            score = 5;
        } else {
            score = 10;
        }
    }

    int score() {
        return score;
    }
}