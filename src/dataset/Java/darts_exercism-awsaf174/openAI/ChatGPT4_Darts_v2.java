class Darts {

    private final double distance;

    Darts(double x, double y) {
        distance = Math.hypot(x, y);
    }

    int score() {
        if (distance <= 1) {
            return 10;
        } else if (distance <= 5) {
            return 5;
        } else if (distance <= 10) {
            return 1;
        } else {
            return 0;
        }
    }
}