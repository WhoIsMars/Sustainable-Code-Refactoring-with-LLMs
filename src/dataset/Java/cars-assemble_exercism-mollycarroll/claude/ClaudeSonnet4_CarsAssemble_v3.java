public class CarsAssemble {
    private static final int BASE_PRODUCTION = 221;
    private static final double EFFICIENCY_HIGH = 0.9;
    private static final double EFFICIENCY_MEDIUM = 0.8;
    private static final double EFFICIENCY_LOW = 0.77;

    public double productionRatePerHour(int speed) {
        double baseRate = speed * BASE_PRODUCTION;
        
        if (speed <= 4) {
            return baseRate;
        } else if (speed < 9) {
            return baseRate * EFFICIENCY_HIGH;
        } else if (speed == 9) {
            return baseRate * EFFICIENCY_MEDIUM;
        } else {
            return baseRate * EFFICIENCY_LOW;
        }
    }

    public int workingItemsPerMinute(int speed) {
        return (int) Math.round(productionRatePerHour(speed) / 60.0);
    }
}