public class CarsAssemble {

    private static final int PRODUCTION_RATE = 221;

    public double productionRatePerHour(int speed) {
        double successRate = (speed <= 4) ? 1.0 :
                             (speed < 9) ? 0.9 :
                             (speed == 9) ? 0.8 : 0.77;
        return speed * PRODUCTION_RATE * successRate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) (productionRatePerHour(speed) / 60);
    }
}