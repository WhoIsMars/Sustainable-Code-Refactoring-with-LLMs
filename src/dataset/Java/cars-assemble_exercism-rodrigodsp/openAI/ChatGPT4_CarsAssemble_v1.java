public class CarsAssemble {

    private static final int PRODUCTION_PER_HOUR = 221;

    public double productionRatePerHour(int speed) {
        double successRate = 1.0;

        if (speed >= 5 && speed < 9) {
            successRate = 0.9;
        } else if (speed == 9) {
            successRate = 0.8;
        } else if (speed == 10) {
            successRate = 0.77;
        }

        return speed * PRODUCTION_PER_HOUR * successRate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) (productionRatePerHour(speed) / 60);
    }
}