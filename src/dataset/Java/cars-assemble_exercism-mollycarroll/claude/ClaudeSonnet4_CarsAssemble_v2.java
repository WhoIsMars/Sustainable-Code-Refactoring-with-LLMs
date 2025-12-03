public class CarsAssemble {
    private static final int BASE_PRODUCTION = 221;
    private static final double EFFICIENCY_5_TO_8 = 0.9;
    private static final double EFFICIENCY_9 = 0.8;
    private static final double EFFICIENCY_10_PLUS = 0.77;

    public double productionRatePerHour(int speed) {
        double baseRate = speed * BASE_PRODUCTION;
        
        if (speed <= 4) {
            return baseRate;
        } else if (speed < 9) {
            return baseRate * EFFICIENCY_5_TO_8;
        } else if (speed == 9) {
            return baseRate * EFFICIENCY_9;
        } else {
            return baseRate * EFFICIENCY_10_PLUS;
        }
    }

    public int workingItemsPerMinute(int speed) {
        double baseRate = speed * BASE_PRODUCTION;
        double hourlyRate;
        
        if (speed <= 4) {
            hourlyRate = baseRate;
        } else if (speed < 9) {
            hourlyRate = baseRate * EFFICIENCY_5_TO_8;
        } else if (speed == 9) {
            hourlyRate = baseRate * EFFICIENCY_9;
        } else {
            hourlyRate = baseRate * EFFICIENCY_10_PLUS;
        }
        
        return (int) Math.round(hourlyRate / 60);
    }
}