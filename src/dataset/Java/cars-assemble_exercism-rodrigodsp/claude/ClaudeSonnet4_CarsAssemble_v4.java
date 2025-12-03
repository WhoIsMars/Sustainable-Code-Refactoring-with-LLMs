public class CarsAssemble {
    private static final double BASE_PRODUCTION = 221.0;
    private static final double EFFICIENCY_90 = 0.9;
    private static final double EFFICIENCY_80 = 0.8;
    private static final double EFFICIENCY_77 = 0.77;
    private static final double MINUTES_PER_HOUR = 60.0;

    public double productionRatePerHour(int speed) {
        double baseProduction = speed * BASE_PRODUCTION;
        
        if (speed >= 5 && speed < 9) {
            return baseProduction * EFFICIENCY_90;
        } else if (speed == 9) {
            return baseProduction * EFFICIENCY_80;
        } else if (speed == 10) {
            return baseProduction * EFFICIENCY_77;
        }
        
        return baseProduction;
    }

    public int workingItemsPerMinute(int speed) {
        return (int)(productionRatePerHour(speed) / MINUTES_PER_HOUR);
    }
}