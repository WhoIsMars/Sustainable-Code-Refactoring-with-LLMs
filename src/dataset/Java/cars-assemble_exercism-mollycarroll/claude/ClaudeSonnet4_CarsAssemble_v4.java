public class CarsAssemble {
    private static final int BASE_PRODUCTION = 221;
    private static final double SUCCESS_RATE_HIGH = 0.9;
    private static final double SUCCESS_RATE_MEDIUM = 0.8;
    private static final double SUCCESS_RATE_LOW = 0.77;
    private static final double MINUTES_PER_HOUR = 60.0;

    public double productionRatePerHour(int speed) {
        double baseRate = speed * BASE_PRODUCTION;
        
        if (speed <= 4) {
            return baseRate;
        } else if (speed < 9) {
            return baseRate * SUCCESS_RATE_HIGH;
        } else if (speed == 9) {
            return baseRate * SUCCESS_RATE_MEDIUM;
        } else {
            return baseRate * SUCCESS_RATE_LOW;
        }
    }

    public int workingItemsPerMinute(int speed) {
        return (int) Math.round(productionRatePerHour(speed) / MINUTES_PER_HOUR);
    }
}