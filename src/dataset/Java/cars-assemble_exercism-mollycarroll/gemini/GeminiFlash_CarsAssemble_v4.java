public class CarsAssemble {

    private static final int PRODUCTION_PER_HOUR = 221;
    private static final double SPEED_LESS_THAN_9_MULTIPLIER = 0.9;
    private static final double SPEED_9_MULTIPLIER = 0.8;
    private static final double SPEED_GREATER_THAN_9_MULTIPLIER = 0.77;
    private static final int MINUTES_PER_HOUR = 60;

    public double productionRatePerHour(int speed) {
        double rate;
        if (speed <= 4) {
            rate = speed * PRODUCTION_PER_HOUR;
        } else if (speed < 9) {
            rate = speed * PRODUCTION_PER_HOUR * SPEED_LESS_THAN_9_MULTIPLIER;
        } else if (speed == 9) {
            rate = speed * PRODUCTION_PER_HOUR * SPEED_9_MULTIPLIER;
        } else {
            rate = speed * PRODUCTION_PER_HOUR * SPEED_GREATER_THAN_9_MULTIPLIER;
        }
        return rate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) Math.round(productionRatePerHour(speed) / MINUTES_PER_HOUR);
    }
}