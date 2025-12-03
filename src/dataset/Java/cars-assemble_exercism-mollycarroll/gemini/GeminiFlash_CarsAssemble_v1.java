public class CarsAssemble {

    private static final int PRODUCTION_PER_HOUR = 221;

    public double productionRatePerHour(int speed) {
        double rate;
        if (speed <= 4) {
            rate = 1.0;
        } else if (speed <= 8) {
            rate = 0.9;
        } else if (speed == 9) {
            rate = 0.8;
        } else {
            rate = 0.77;
        }
        return speed * PRODUCTION_PER_HOUR * rate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) (productionRatePerHour(speed) / 60);
    }
}