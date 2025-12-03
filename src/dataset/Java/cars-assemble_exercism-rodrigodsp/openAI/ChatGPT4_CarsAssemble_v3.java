public class CarsAssemble {

    private static final int BASE_PRODUCTION_RATE = 221;

    public double productionRatePerHour(int speed) {
        double successRate = switch (speed) {
            case 1, 2, 3, 4 -> 1.0;
            case 5, 6, 7, 8 -> 0.9;
            case 9 -> 0.8;
            case 10 -> 0.77;
            default -> 0.0;
        };
        return speed * BASE_PRODUCTION_RATE * successRate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) (productionRatePerHour(speed) / 60);
    }
}