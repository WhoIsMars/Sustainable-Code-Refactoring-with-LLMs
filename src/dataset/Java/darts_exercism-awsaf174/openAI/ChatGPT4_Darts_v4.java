class Darts {

    private final double distance;

    Darts(double x, double y) {
        distance = Math.hypot(x, y);
    }

    int score() {
        if (distance <= 1) return 10;
        if (distance <= 5) return 5;
        if (distance <= 10) return 1;
        return 0;
    }
}