public class CarsAssemble {
    private static final int BASE_PRODUCTION = 221;
    private static final double EFFICIENCY_5_TO_8 = 0.9;
    private static final double EFFICIENCY_9 = 0.8;
    private static final double EFFICIENCY_10 = 0.77;
    private static final double MINUTES_PER_HOUR = 60.0;

    public double productionRatePerHour(int speed) {
        double baseProduction = speed * BASE_PRODUCTION;
        
        if (speed >= 5 && speed <= 8) {
            return baseProduction * EFFICIENCY_5_TO_8;
        } else if (speed == 9) {
            return baseProduction * EFFICIENCY_9;
        } else if (speed == 10) {
            return baseProduction * EFFICIENCY_10;
        }
        
        return baseProduction;
    }

    public int workingItemsPerMinute(int speed) {
        return (int)(productionRatePerHour(speed) / MINUTES_PER_HOUR);
    }
}