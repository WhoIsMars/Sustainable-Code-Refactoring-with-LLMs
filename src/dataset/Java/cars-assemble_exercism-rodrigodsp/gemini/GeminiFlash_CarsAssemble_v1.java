public class CarsAssemble {

    private static final int CARS_PER_HOUR = 221;

    public double productionRatePerHour(int speed) {
        double production = speed * CARS_PER_HOUR;
        double successRate;

        if (speed >= 5 && speed <= 8) {
            successRate = 0.9;
        } else if (speed == 9) {
            successRate = 0.8;
        } else if (speed == 10) {
            successRate = 0.77;
        } else {
            return production; // Early return for speeds outside the discount range
        }

        return production * successRate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int)(productionRatePerHour(speed) / 60.0);
    }
}